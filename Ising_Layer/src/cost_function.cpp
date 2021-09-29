#include "mylib.h"
#include "cost_function.h"
#include <cassert>
#include <vector>

using namespace std;

Graph reverse(const Graph& G) {
  const int n = G.size();
  Graph revG(n);
  rep(i, n) for (auto&& e : G[i]) {
    revG[e.to].emplace_back(i, e.weight);
  }
  return revG;
}

CostFunction::CostFunction(const Graph& J1, const vector<Weight>& h1, const Graph& J2, const vector<Weight>& h2, const Weight A, const Weight B)
  : J1(J1), J2(J2), revJ1(reverse(J1)), revJ2(reverse(J2)), h1(h1), h2(h2), A(A), B(B) {}
CostFunction::CostFunction(const Graph& J, const vector<Weight>& h)
  : CostFunction(J, h, J, h, 1, 0) {}

size_t CostFunction::size() const {
  assert(J1.size() == h1.size() && h1.size() == h2.size() && J2.size() == h2.size());
  return J1.size();
}

Weight calcEnergyDiff(const vector<int>& spin, const int node_id, const Graph& J, const Graph& revJ, const vector<Weight>& h) {
  Weight res = h[node_id];
  for (auto&& e : J[node_id]) {
    if (e.to == node_id) continue;
    res += spin[e.to] * e.weight;
  }
  for (auto&& e : revJ[node_id]) {
    if (e.to == node_id) continue;
    res += spin[e.to] * e.weight;
  }
  return res;
}
Weight CostFunction::calcEnergyDiff(const double per, const vector<int>& spin, const int node_id) const {
  assert(0 <= per && per <= 1);
  return getCurrentA(per) * ::calcEnergyDiff(spin, node_id, J1, revJ1, h1) + getCurrentB(per) * ::calcEnergyDiff(spin, node_id, J2, revJ2, h2);
}

Weight calcEnergy(const vector<int>& spin, const Graph& J, const vector<Weight>& h) {
  const size_t V = J.size();
  assert(spin.size() == V);
  Weight res{};
  rep(i, V) for (auto&& e : J[i]) {
    res += spin[i] * spin[e.to] * e.weight;
  }
  rep(i, V) {
    res += spin[i] * h[i];
  }
  return res;
}
Weight CostFunction::calcEnergy(const double per, const vector<int>& spin) const {
  assert(0 <= per && per <= 1);
  return getCurrentA(per) * ::calcEnergy(spin, J1, h1) + getCurrentB(per) * ::calcEnergy(spin, J2, h2);
}

Weight CostFunction::getCurrentA(const double per) const {
  assert(0 <= per && per <= 1);
  // return A * (1-per);
  return A;
}
Weight CostFunction::getCurrentB(const double per) const {
  assert(0 <= per && per <= 1);
  // return B * per;
  return B;
}

pair<Graph, vector<Weight>> to01(const Graph& J, const vector<Weight>& h) {
  assert(J.size() == h.size());
  const int V = h.size();
  vector<Weight> nh(V, 0);
  rep(i, V) nh[i] += 2 * h[i];
  rep(i, V) each(e, J[i]) {
    nh[i] += e.weight;
    nh[e.to] += e.weight;
  }
  return {J, nh};
}
CostFunction CostFunction::to01() const {
  auto result1 = ::to01(J1, h1);
  auto result2 = ::to01(J2, h2);
  return CostFunction(result1.first, result1.second, result2.first, result2.second, A, B);
}
