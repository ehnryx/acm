#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());


int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#ifdef USING_FAST_INPUT
  fast_input cin;
#endif

  int r;
  cin >> r;
  int l = 1;
  for(int t=1; ; t++) {
    int m = (l + r) / 2;
    cout << m * t << endl;
    string s;
    cin >> s;
    if(s == "less") {
      r = m - 1;
    } else if(s == "more") {
      l = m + 1;
    } else {
      return 0;
    }
  }
  assert(false); // kurwa

  return 0;
}
