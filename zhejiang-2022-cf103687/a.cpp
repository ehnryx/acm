#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
//%:include "utility/output.h"

using ll = long long;
using ld = long double;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

void solve() {
  int a, b;
  cin >> a >> b;
  if(a == b) {
    cout << 0 << nl;
  } else if(a < b) {
    if(a % 2 != b % 2) {
      cout << 1 << nl;
    } else if((b - a) / 2 % 2 == 1) {
      cout << 2 << nl;
    } else {
      cout << 3 << nl;
    }
  } else {
    if(a % 2 == b % 2) {
      cout << 1 << nl;
    } else {
      cout << 2 << nl;
    }
  }
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#ifdef USING_FAST_INPUT
  fast_input cin;
#endif

  int T;
  cin >> T;
  while(T--) {
    solve();
  }

  return 0;
}
