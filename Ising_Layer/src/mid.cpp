#include "ising_solver.h"
#include "mid.h"
#include "mylib.h"
#include <vector>
#include <cassert>

using namespace std;

#define NODE(step, v) (n * (step) + (v))

Mid::Mid(const Problem& prob) : prob(prob) {}
Mid::~Mid() {}
CostFunction Mid::getCostFunction() {
  const int n = prob.size();
  Graph J1(n * n), J2(n * n);
  vector<Weight> h1(n * n, 0), h2(n * n, 0);
  rep(i, n) rep(j, n) rep(step, n) {
    Weight dist = abs(prob.points[i] - prob.points[j]) * Base;
    J1[NODE(step, i)].emplace_back(
      NODE((step+1)%n, j), dist
    );
  }
  rep(i, n) rep(j, n) rep(k, n) {
    Weight cost = Base;
    J2[NODE(i, j)].emplace_back(
      NODE(i, k), cost
    );
    J2[NODE(i, j)].emplace_back(
      NODE(k, j), cost
    );
  }
  rep(i, h2.size()) h2[i] -= 4 * Base;
  // return CostFunction(J2, h2).to01();
  return CostFunction(J1, h1, J2, h2, 1, 1e5).to01();
}
Answer Mid::getAnswerFromSpin(const vector<int>& spin) const {
  const int n = prob.size();
  vector<int> order;
  rep(step, n) rep(v, n) {
    assert(NODE(step, v) >= 0);
    assert(NODE(step, v) < int(spin.size()));
    if (spin[NODE(step, v)] > 0) {
      order.push_back(v);
      break;
    }
  }
  return Answer(prob, move(order));
}
