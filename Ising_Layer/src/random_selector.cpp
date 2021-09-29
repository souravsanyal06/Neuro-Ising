#include "mylib.h"
#include "random_selector.h"
#include <vector>
#include <random>
#include <cassert>

using namespace std;

int expand(const int n) {
  int res = 1;
  while (res < n) res <<= 1;
  return res;
}

RandomSelector::SegmentTree::SegmentTree(int size) : size_(size), n(expand(size)), val(expand(size)*2, 0) {
  rep(i, size) {
    val[n + i] = 1;
  }
  rrep(i, 1, n) {
    val[i] = val[i*2] + val[i*2+1];
  }
}
void RandomSelector::SegmentTree::update(int pos, int value) {
  assert(0 <= pos && pos < size_);
  pos += n;
  val[pos] = value;
  while (pos /= 2) {
    val[pos] = val[pos*2] + val[pos*2+1];
  }
}
int RandomSelector::SegmentTree::argsum(int sum) const {
  int v = 1;
  assert(val[v] >= sum);
  if (sum == 0) return 0;
  while (v < n) {
    if (val[v * 2] < sum) {
      sum -= val[v * 2];
      v = v * 2 + 1;
    }
    else {
      v = v * 2 + 0;
    }
  }
  assert(sum == 1);
  return v - n + 1;
}
size_t RandomSelector::SegmentTree::size() const {
  return size_t(size_);
}


RandomSelector::RandomSelector(const int max_n) : seg(max_n) {}
template<class RandomDevice>
vector<int> RandomSelector::select(const int n, RandomDevice&& rnd) {
  assert(0 <= n && n <= int(size()));
  vector<int> res;
  res.reserve(n);
  rep(i, n) {
    int pos = rnd() % (size() - i);
    int pickup = seg.argsum(pos+1) - 1;
    res.push_back(pickup);
    seg.update(pickup, 0);
  }
  for (auto&& pickup : res) {
    seg.update(pickup, 1);
  }
  return res;
}
size_t RandomSelector::size() const {
  return seg.size();
}

template std::vector<int> RandomSelector::select<std::mt19937&>(const int n, std::mt19937& rnd);
