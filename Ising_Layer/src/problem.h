#ifndef __problem__
#define __problem__

#include "ising_solver.h"
#include <vector>
#include <complex>

class Answer;
class Problem {
public:
  std::vector<std::complex<double>> points;
  Problem(std::vector<std::complex<double>>&& points);
  size_t size() const;
  static Problem fromIstream(std::istream& is);
};
class Answer {
  const Problem prob;
  const std::vector<int> order;
public:
  Answer(const Problem& prob, const std::vector<int>& order);
  void output(std::ostream& os, bool is_detail) const;
  bool verify() const;
};

#endif
