#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());


int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);

  int n, m, c, r;
  cin >> n >> m >> c >> r;

  vector<tuple<int, int, ld>> ev;
  for(int i=0; i<c; i++) {
    int a, b, v;
    ld p;
    cin >> a >> b >> p >> v;
    ev.emplace_back(a, 1, p*v);
    ev.emplace_back(b, -1, p*v);
  }
  for(int i=0; i<=m; i++) {
    ev.emplace_back(i, 7, 0);
  }
  sort(begin(ev), end(ev));
  vector<ld> rain(m + 1);
  ld cur = 0;
  for(auto [t, put, v] : ev) {
    cur += put*v;
    // rain in the coming interval
    if(put == 7) {
      rain[t] = cur;
    }
  }

  vector<bool> roof(n + 2);
  for(int i=0; i<r; i++) {
    int a, b;
    cin >> a >> b;
    for(int j=a+1; j<=b; j++) {
      roof[j] = true;
    }
  }
  roof[0] = true;

  vector dp(n+1, vector<ld>(m+1, numeric_limits<ld>::infinity()));
  dp[0][0] = 0;

  for(int i=0; i<=n; i++) {
    for(int j=1; j<=m; j++) {
      ld wait = (roof[i] || roof[i+1] ? 0 : rain[j-1]);
      dp[i][j] = dp[i][j-1] + wait;
      if (i > 0) {
        ld go = (roof[i] ? 0 : rain[j-1]);
        dp[i][j] = min(dp[i][j], dp[i-1][j-1] + go);
      }
    }
  }

  cout << dp[n][m] << nl;

  return 0;
}
