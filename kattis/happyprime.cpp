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


int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#ifdef USING_FAST_INPUT
  fast_input cin;
#endif

  int T;
  cin >> T;
  while(T--) {
    int tt, n;
    cin >> tt >> n;
    int s = n;
    // 1, 1  (OK)
    // 2, 4
    // 3, 9
    // 4, 16
    // 5, 25, 29, 85
    // 6, 36, 45, 41, 17, 50
    // 7, 49, 97, 130, 10  (OK)
    // 8, 64, 52
    // 9, 81, 65, 61, 37, 58, 89, 145, 42, 20
    while(s >= 10) {
      string m = to_string(s);
      s = 0;
      for(char c : m) {
        s += (c - '0') * (c - '0');
      }
    }
    if(s != 1 && s != 7) {
      cout << tt << " " << n << " NO" << nl;
      continue;
    }

    bool p = true;
    if(n == 1 || (n > 2 && n % 2 == 0)) {
      p = false;
    }
    for(int d=3; d*d<=n; d+=2) {
      if(n % d == 0) {
        p = false;
        break;
      }
    }
    if(!p) {
      cout << tt << " " << n << " NO" << nl;
      continue;
    }

    cout << tt << " " << n << " YES" << nl;
  }

  return 0;
}
