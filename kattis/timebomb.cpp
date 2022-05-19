#include <bits/stdc++.h>
using namespace std;

%:include "utility/fast_input.h"

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

vector<string> nums = {
  "***   * *** *** * * *** *** *** *** ***",
  "* *   *   *   * * * *   *     * * * * *",
  "* *   * *** *** *** *** ***   * *** ***",
  "* *   * *     *   *   * * *   * * *   *",
  "***   * *** ***   * *** ***   * *** ***",
};

int f(auto g, int c) {
  for(int d=0; d<10; d++) {
    bool ok = true;
    for(int i=0; i<5; i++) {
      for(int j=0; j<3; j++) {
        ok &= (nums[i][4*d+j] == g[i][c+j]);
      }
    }
    if(ok) return d;
  }
  return -1;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#ifdef USING_FAST_INPUT
  fast_input cin;
#endif

  auto g = cin.readlines(5);
  int sum = 0;
  int last = 0;
  for(int i=0; i<g[0].size(); i+=4) {
    last = f(g, i);
    if(last == -1) {
      cout << "BOOM!!" << nl;
      return 0;
    }
    sum += last;
  }

  if(sum % 3 == 0 && last % 2 == 0) {
    cout << "BEER!!" << nl;
  } else {
    cout << "BOOM!!" << nl;
  }

  return 0;
}
