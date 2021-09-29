#include "../src/mylib.h"
#include "../src/random_selector.h"
#include "../src/random_selector.cpp"

#include <vector>
#include <random>
#include <algorithm>

int main() {
  using namespace std;
  mt19937 rnd(0);
  RandomSelector rs1(1);
  assert(rs1.size() == 1);
  assert(rs1.select(1, rnd)[0] == 0);
  assert(rs1.select(1, rnd).size() == 1);
  const int n = 1000, m = 900;
  RandomSelector rs2(n);
  assert(rs2.size() == n);
  assert(rs2.select(n, rnd).size() == n);
  cout << endl;
  vector<int> result = rs2.select(m, rnd);
  assert(result.size() == m);
  result.erase(unique(result.begin(), result.end()), result.end());
  assert(result.size() == m);
  for (auto&& x : result) {
    assert(0 <= x && x < n);
  }
}
