#include "mylib.h"
#include "ising_solver.h"
#include "cost_function.h"
#include <vector>
#include <random>
#include <cassert>
#include <cmath>

using namespace std;

Edge::Edge(int to, Weight weight) : to(to), weight(weight) {}

IsingSolver::IsingSolver(const CostFunction& cf)
  : steps(0), total_step(0),
    random_selector(cf.size()), active_ratio(0), cf(cf) {}

int IsingSolver::calcTotalStep(double initial_active_ratio) const {
  // return n s.t. initial_active_ratio * size() * cool_coe^n < 1
  double n = - (log(initial_active_ratio) + log(size())) / log(cool_coe);
  assert(n >= 0);
  return int(ceil(n));
}

void IsingSolver::init(const IsingSolver::InitMode mode, const int seed, const double cool_coe, const double update_ratio, const double initial_active_ratio) {
  assert(0 <= cool_coe && cool_coe < 1);
  assert(0 <= update_ratio && update_ratio <= 1);
  rnd.seed(seed);
  this->cool_coe = cool_coe;
  this->update_ratio = update_ratio;
  this->steps = 0;
  this->active_ratio = initial_active_ratio;
  this->total_step = calcTotalStep(initial_active_ratio);
  switch (mode) {
    case Negative:
      current_spin.assign(size(), -1);
      break;
    case Positive:
      current_spin.assign(size(), 1);
      break;
    case Random:
      current_spin.resize(size());
      for (auto&& s : current_spin) {
        s = rnd() % 2 ? 1 : -1;
      }
      break;
  }
  optimal_spin = current_spin;
}
void IsingSolver::init(const IsingSolver::InitMode mode, const double cool_coe, const double update_ratio, const double initial_active_ratio) {
  random_device rd;
  init(mode, rd(), cool_coe, update_ratio, initial_active_ratio);
}
void IsingSolver::randomFlip() {
  vector<int> node_ids = random_selector.select(getActiveNodeCount(), rnd);
  for (auto&& node_id : node_ids) {
    current_spin[node_id] = 1;
    if (current_spin[node_id] > 0) {
      for (auto&& e : cf.J2[node_id]) {
        // if (int(rnd() % 100) * getTotalStep() < getStep() * 100 * 5) {
          current_spin[e.to] = -1;
        // }
      }
    }
  }
}
void IsingSolver::updateNodes() {
  vector<int> node_ids = random_selector.select(getUpdateNodeCount(), rnd);
  for (auto&& node_id : node_ids) {
    updateNode(node_id);
  }
}
void IsingSolver::updateNode(const int node_id) {
  Weight energy_diff = cf.calcEnergyDiff(getCurrentPer(), current_spin, node_id);
  if (energy_diff > 0) {
    current_spin[node_id] = -1;
  }
  else if (energy_diff < 0) {
    current_spin[node_id] = 1;
  }
  else {
    current_spin[node_id] = rnd() % 2 ? 1 : -1;
  }
}
void IsingSolver::cool() {
  active_ratio *= cool_coe;
}
void IsingSolver::updateOptimalSpin() {
  if (getCurrentEnergy() < getOptimalEnergy()) {
    optimal_spin = current_spin;
  }
}
void IsingSolver::step() {
  cool();
  if (current_spin.size() != size()) {
    throw new runtime_error("call init method first");
  }
  randomFlip();
  updateNodes();
  updateOptimalSpin();
  ++steps;
}
size_t IsingSolver::getActiveNodeCount() const {
  return size_t(floor(size() * active_ratio));
}
size_t IsingSolver::getUpdateNodeCount() const {
  return size_t(floor(size() * update_ratio));
}
size_t IsingSolver::size() const {
  return cf.size();
}
Weight IsingSolver::calcEnergy(const std::vector<int>& spin) const {
  return cf.calcEnergy(getCurrentPer(), spin);
}
Weight IsingSolver::getCurrentEnergy() const {
  return calcEnergy(current_spin);
}
Weight IsingSolver::getOptimalEnergy() const {
  return calcEnergy(optimal_spin);
}
const vector<int>& IsingSolver::getCurrentSpin() const {
  return current_spin;
}
const vector<int>& IsingSolver::getOptimalSpin() const {
  return optimal_spin;
}
void IsingSolver::setCurrentSpin(const vector<int>& new_spin) {
  assert(current_spin.size() == new_spin.size());
  current_spin = new_spin;
}
int IsingSolver::getStep() const {
  return steps;
}
int IsingSolver::getTotalStep() const {
  return total_step;
}
double IsingSolver::getCurrentPer() const {
  return min(1.0, double(getStep()) / getTotalStep());
}
