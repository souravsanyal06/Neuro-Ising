#ifndef __random_selector__
#define __random_selector__

#include <vector>
#include <random>

class RandomSelector {
  class SegmentTree {
    int size_, n;
    std::vector<int> val;
  public:
    SegmentTree(int size);
    void update(int pos, int value);
    int argsum(const int sum) const;
    size_t size() const;
  };
  SegmentTree seg;
public:
  RandomSelector(const int max_n);
  template<class RandomDevice>
  std::vector<int> select(const int n, RandomDevice&& rnd);
  size_t size() const;
};

#endif
