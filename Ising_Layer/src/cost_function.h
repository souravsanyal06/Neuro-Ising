#ifndef __cost_function__
#define __cost_function__

#include <vector>
#include "cost_function.h"

using Weight = long long;

struct Edge {
  int to;
  Weight weight;
  Edge(int to, Weight weight);
};

using Graph = std::vector<std::vector<Edge>>;

class CostFunction {
public:
  const Graph J1, J2, revJ1, revJ2;
  const std::vector<Weight> h1, h2;
  const Weight A, B;
  CostFunction(const Graph& J1, const std::vector<Weight>& h1, const Graph& J2, const std::vector<Weight>& h2, const Weight A, const Weight B);
  CostFunction(const Graph& J, const std::vector<Weight>& h);
  size_t size() const;
  Weight calcEnergyDiff(const double per, const std::vector<int>& spin, const int node_id) const;
  Weight calcEnergy(const double per, const std::vector<int>& spin) const;
  CostFunction to01() const;
  Weight getCurrentA(const double per) const;
  Weight getCurrentB(const double per) const;
};

#endif
