#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
//%:include "utility/output.h"
%:include "number/mod_int.h"

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

using Int = mod_int<MOD>;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#ifdef USING_FAST_INPUT
  fast_input cin;
#endif

  ll n, m;
  cin >> n >> m;

  if(n > 60) {
    cout << 0 << nl;
    return 0;
  }

  vector<ll> cnt(61, 0);
  for(int i=1; i<=60; i++) {
    ll base = 1ll << (i-1);
    if(base > m) {
      cnt[i] = 0;
    } else {
      cnt[i] = min(m + 1, (1ll << i)) - base;
    }
  }

  vector dp(n+1, vector<Int>(61, 0));
  dp[0][0] = 1;
  for(int i=1; i<=n; i++) {
    for(int j=1; j<=60; j++) {
      for(int k=0; k<j; k++) {
        dp[i][j] += dp[i-1][k] * cnt[j];
      }
    }
  }
  cout << accumulate(begin(dp[n]), end(dp[n]), Int(0)) << nl;

  return 0;
}
