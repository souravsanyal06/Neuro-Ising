#include "ising_solver.h"
#include "mid_grid.h"
#include "mylib.h"
#include <vector>
#include <cassert>
#include <tuple>

using namespace std;

vector<pair<int, int>> make_ord(int n) {
  assert(n >= 2 && n % 2 == 0);
  vector<pair<int, int>> res;
  rep(i, n/2) {
    rep(x, 1, n) res.emplace_back(x, i*2);
    rrep(x, 1, n) res.emplace_back(x, i*2+1);
  }
  rrep(y, n) res.emplace_back(0, y);
  return res;
}
MidWithGrid::MidWithGrid(const Problem& prob, int grid_size) : Mid(prob), grid_size(grid_size) {}
MidWithGrid::~MidWithGrid() {}
CostFunction MidWithGrid::getCostFunction() {
  assert(grid_size % 2 == 0);
  assert(grid_size >= 2);
  const int n = prob.size();
  vector<vector<vector<int>>> grid(grid_size, vector<vector<int>>(grid_size));
  const double linf = 1e12;
  // Create rectangle
  double min_x = linf, max_x = -linf, min_y = linf, max_y = -linf;
  rep(i, n) {
    min_x = min(min_x, prob.points[i].real());
    max_x = max(max_x, prob.points[i].real());
    min_y = min(min_y, prob.points[i].imag());
    max_y = min(max_y, prob.points[i].imag());
  }
  // Sort vertices into grid
  const double width = max_x - min_x, height = max_y - min_y;
  rep(i, n) {
    int xid = (prob.points[i].real() - min_x - eps) / width * grid_size;
    int yid = (prob.points[i].real() - min_x - eps) / height * grid_size;
    assert(0 <= xid && xid < grid_size);
    assert(0 <= yid && yid < grid_size);
    grid[yid][xid].push_back(i);
  }
  // Visit order
  vector<pair<int, int>> ord = make_ord(grid_size);
  // Set of vertices that can be visited in the i-th step
  vector<vector<int>> step_to_nodes(n), node_to_nodes(n);
  ising_node.clear();
  int base_step = 0;
  for (auto&& p : ord) {
    int x, y; tie(x, y) = p;
    int gsz = grid[y][x].size();
    rep(i, gsz) for (auto&& v : grid[y][x]) {
      int nid = ising_node.size();
      ising_node.emplace_back(base_step + i, v);
      step_to_nodes[base_step + i].push_back(nid);
      node_to_nodes[v].push_back(nid);
    }
    base_step += gsz;
  }
  // J, h Build
  Graph J1(n * n), J2(n * n);
  vector<Weight> h1(n * n, 0), h2(n * n, 0);
  rep(step, n) for (auto&& n1 : step_to_nodes[step]) for (auto&& n2 : step_to_nodes[(step+1)%n]) {
    int v1 = ising_node[n1].second;
    int v2 = ising_node[n2].second;
    Weight dist = abs(prob.points[v1] - prob.points[v2]) * Base;
    J1[n1].emplace_back(n2, dist);
  }
  // Visit onlt one vertex at each step
  rep(step, n) for (auto&& n1 : step_to_nodes[step]) for (auto&& n2 : step_to_nodes[step]) {
    if (n1 == n2) continue;
    J2[n1].emplace_back(n2, Base);
  }
  // Do not visit the same vertex more than once
  rep(i, n) for (auto&& n1 : node_to_nodes[i]) for (auto&& n2 : node_to_nodes[i]) {
    if (n1 == n2) continue;
    J2[n1].emplace_back(n2, Base);
  }
  rep(i, h2.size()) h2[i] -= 4 * Base;
  // return CostFunction(J2, h2).to01();
  return CostFunction(J1, h1, J2, h2, 1, 1e5).to01();
}
Answer MidWithGrid::getAnswerFromSpin(const vector<int>& spin) const {
  const int n = prob.size();
  vector<int> order(n, -1);
  rep(i, ising_node.size()) {
    if (spin[i] > 0) {
      order[ising_node[i].first] = ising_node[i].second;
    }
  }
  vector<int> norder;
  rep(i, order.size()) {
    if (order[i] < 0) continue;
    norder.push_back(order[i]);
  }
  return Answer(prob, move(norder));
}
