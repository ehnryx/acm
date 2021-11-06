#include <bits/stdc++.h>
using namespace std;

#include "../../lca/number/mod_int.h"

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int MOD = 1e9 + 7;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

using Int = mod_int<MOD>;

const int M = 2000;
Int dp[4][M][2];

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);

  int T;
  cin >> T;
  while(T--) {
    string s;
    cin >> s;
    int n = s.size();
    for(int i=0; i<n; i++) {
      dp[0][i][1].assign(1);
      dp[0][i][0].assign(1);
      dp[3][i][0].assign(0);
    }
    for(int d=1; d<n; d++) {
      int r = d & 0b11;
      int u = (d - 1) & 0b11;
      int u2 = (d - 2) & 0b11;
      for(int i=0; i+d<n; i++) {
        // use left
        dp[r][i][1] = dp[u][i][1];
        if(s[i] == s[i+d]) {
          dp[r][i][1] += dp[u2][i+1][0] + Int(1);
        }
        // other
        dp[r][i][0] = dp[r][i][1] + dp[u][i+1][0];
      }
    }
    cout << dp[(n-1) & 0b11][0][0] << nl;
  }

  return 0;
}
