#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int MOD = 1e9 + 7;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());


int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);

  int n, m;
  cin >> n >> m;

  // must shoot min(n, m) ghosts
  int s = min(n, m); // m choose s ways to choose these ghosts
  vector ncr(m+1, vector<int>(m+1));
  for(int i=0; i<=m; i++) {
    ncr[i][0] = ncr[i][i] = 1;
    for(int j=1; j<i; j++) {
      ncr[i][j] = ncr[i-1][j] + ncr[i-1][j-1];
      if(ncr[i][j] >= MOD) ncr[i][j] -= MOD;
    }
  }

  // dp[i][j] = # of ways for the first i ghostbusters to aim at the first j ghosts
  // transition: add a new ghostbuster x, x can aim at the last ghost or
  // the next ghost if there are any left. ie. dp[i][j] = dp[i-1][j-1] + dp[i-1][j]
  vector dp(n+1, vector<int>(m+1));
  dp[0][0] = 1;
  for(int i=1; i<=n; i++) {
    for(int j=1; j<=s; j++) {
      dp[i][j] = dp[i-1][j] + dp[i-1][j-1];
      if(dp[i][j] >= MOD) dp[i][j] -= MOD;
    }
  }
  cout << (ll)dp[n][s] * ncr[m][s] % MOD << nl;

  return 0;
}
