#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
//%:include "utility/output.h"

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

  int n, m; ld p;
  cin >> n >> m >> p;

  vector<ld> fail(n+1);
  fail[0] = 1;
  for(int i=1; i<=n; i++) {
    fail[i] = fail[i-1] * p;
  }
  fail[1] = 0; // must take

  vector dp(2, vector<ld>(n+1));
  dp[0][n] = 1;
  for(int i=0; i<m; i++) {
    int id = i & 1;
    for(int j=n; j>0; j--) {
      // fail
      dp[id][j-1] += dp[id][j] * fail[j];
      // fall
      dp[id^1][j-1] += dp[id][j] * (1 - fail[j]) / 2;
      // safe
      dp[id^1][j] += dp[id][j] * (1 - fail[j]) / 2;
    }
    fill(begin(dp[id]), end(dp[id]), 0);
  }
  cout << accumulate(begin(dp[m&1]) + 1, end(dp[m&1]), (ld)0) << nl;

  return 0;
}
