#include "mylib.h"
#include "problem.h"
#include "ising_solver.h"
#include "cost_function.h"
#include <cassert>
#include <complex>

using namespace std;

vector<complex<double>> points;
Problem::Problem(vector<complex<double>>&& points) : points(points) {}
size_t Problem::size() const {
  return points.size();
}
Problem Problem::fromIstream(std::istream& is) {
  int n; is >> n;
  vector<complex<double>> points;
  points.reserve(n);
  rep(i, n) {
    double x, y; is >> x >> y;
    points.emplace_back(x, y);
  }
  return Problem(move(points));
}
bool Answer::verify() const {
  if (order.size() != prob.size()) return false;
  rep(i, order.size()) rep(j, i) {
    if (order[i] == order[j]) {
      return false;
    }
  }
  return true;
}

Answer::Answer(const Problem& prob, const vector<int>& order) : prob(prob), order(order) {}
void Answer::output(ostream& os, bool is_detail) const {
  //if (is_detail) os << "order: "<< endl;
  double sum = 0;
  if (order.size() > 0) {
    rep(i, order.size()) {
      //if (i && is_detail) os << " -> ";
      assert(order[i % order.size()] >= 0);
      assert(order[i % order.size()] < int(prob.size()));
      auto point = prob.points[order[i % order.size()]];
      //if (is_detail) os << "(" << point.real() << ", " << point.imag() << ")";
      if (is_detail) os << point.real() << " " << point.imag() << endl;
    }
    rep(i, order.size()-1) {
      sum += abs(prob.points[order[(i+1) % order.size()]] - prob.points[order[i]]);
     // os << sum << endl;
    }
  }
  if (is_detail) os << endl;
  os  << "dist " << sum << endl;
}

