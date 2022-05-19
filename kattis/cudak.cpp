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

ll solve(ll num, int m) {
  string s = to_string(num);
  int n = size(s);
  vector dp(n+1, vector(m+1, vector<ll>(2)));
  dp[0][0][1] = 1; // 0 length, 0 sum, follow
  for(int i=0; i<n; i++) {
    for(int j=0; j<=m; j++) {
      for(int d=0; d<=9 && d<=j; d++) {
        if(d == s[i] - '0') {
          dp[i+1][j][1] += dp[i][j-d][1];
        }
        if(d < s[i] - '0') {
          dp[i+1][j][0] += dp[i][j-d][1];
        }
        dp[i+1][j][0] += dp[i][j-d][0];
      }
    }
  }
  return dp[n][m][0] + dp[n][m][1];
}

ll smallest(ll num, int m) {
  string s = to_string(num);
  int n = 15;
  s = string(n - size(s), '0') + s; // wtf
  ll big = numeric_limits<ll>::max() / 2;
  vector dp(n+1, vector(m+1, vector<ll>(2, big)));
  dp[0][0][1] = 0; // 0 length, 0 sum, follow
  for(int i=0; i<n; i++) {
    ll t = llround(pow(10, n-1-i));
    for(int j=0; j<=m; j++) {
      for(int d=0; d<=9 && d<=j; d++) {
        if(d == s[i] - '0') {
          dp[i+1][j][1] = min(dp[i+1][j][1], dp[i][j-d][1] + t*d);
        }
        if(d > s[i] - '0') {
          dp[i+1][j][0] = min(dp[i+1][j][0], dp[i][j-d][1] + t*d);
        }
        dp[i+1][j][0] = min(dp[i+1][j][0], dp[i][j-d][0] + t*d);
      }
    }
  }
  return min(dp[n][m][0], dp[n][m][1]);
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#ifdef USING_FAST_INPUT
  fast_input cin;
#endif

  ll a, b;
  cin >> a >> b;
  int s;
  cin >> s;
  cout << solve(b, s) - solve(a - 1, s) << nl;
  cout << smallest(a, s) << nl;

  return 0;
}
