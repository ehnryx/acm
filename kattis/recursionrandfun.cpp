#include <bits/stdc++.h>
using namespace std;

//%:include "io/fast_input.h"

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

  for(int a, b, c, i, k; cin >> a >> b >> c >> i >> k;) {
    int lb = (i + c - 1) / c;
    int ub = i;
    bool ok = false;
    for(int j=lb; j<=ub; j++) {
      ok |= (a * j + 1 <= k && k <= (a + b-1) * j + 1);
    }
    cout << (ok ? "possible" : "impossible") << nl;
  }

  return 0;
}
