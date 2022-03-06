#include <bits/stdc++.h>
using namespace std;

#include "../../lca/math/matrix.h"
#include "../../lca/number/float_with_eps.h"

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

using Float = float_with_eps<ld, 1e-11L>;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);

  int n;
  cin >> n;
  vector<ld> p(n+1);
  for(int i=1; i<=n; i++) {
    cin >> p[i];
  }

  vector<int> s(n+1);
  for(int i=1; i<=n; i++) {
    cin >> s[i];
  }

  // dp[pos][unused][up]
  vector dp(n+1, vector<ld>(1<<n));
  dp[0][(1<<n)-1] = 1;
  for(int i=1; i<=n; i++) {
    // go from s[i-1] to s[i]
    int m = 2*s[i] + 1;
    int delta = s[i] - s[i-1];

    for(int archer=1; archer<=n; archer++) {
      matrix<Float> mat(m, m + 1);
      // P(0) = 0
      mat[0][0] = 1;
      mat[0][m] = 0;
      // P(m-1) = 1
      mat[m-1][m-1] = 1;
      mat[m-1][m] = 1;
      for(int j=1; j<m-1; j++) {
        // P(j) = (1-p)*P(j-1) + p*P(j+1)
        mat[j][j] = -1;
        mat[j][j-1] = 1 - p[archer]; // miss
        mat[j][j+1] = p[archer];     // hit
      }
      mat.solve();
      ld up_up = mat.ans[m - 1 - delta].to_float();
      ld down_up = mat.ans[delta].to_float();
      //cerr << "( " << i << ", " << archer << " ): " << up_up << " " << down_up << endl;
      //cerr << "m: " << m << " and delta " << delta << endl;

      int j = archer - 1;
      for(int bm=0; bm<1<<n; bm++) {
        if(!(bm >> j & 1)) continue;
        ld to_up = dp[i-1][bm] * up_up + (1 - dp[i-1][bm]) * down_up;
        dp[i][bm^1<<j] = max(dp[i][bm^1<<j], to_up);
      }
    }
  }

  cout << dp[n][0] << nl;

  return 0;
}
