#ifndef __mid__
#define __mid__

#include "ising_solver.h"
#include "problem.h"
#include <vector>

class Mid {
protected:
  const Weight Base = 1e3;
  const Problem prob;
public:
  Mid(const Problem& prob);
  virtual ~Mid();
  virtual CostFunction getCostFunction();
  virtual Answer getAnswerFromSpin(const std::vector<int>& spin) const;
};

#endif
