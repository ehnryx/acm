#include <bits/stdc++.h>
using namespace std;

%:include "io/fast_input.h"

using ll = long long;
using ld = /*long*/ double;
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

  for(int n, v; cin >> n >> v && n; ) {
    vector<pt> a;
    a.reserve(n + 1);
    for(int i=0; i<n; i++) {
      int x, y;
      cin >> x >> y;
      a.emplace_back(x, y);
    }
    a.emplace_back(0, 0);

    vector<ld> rise(n);
    vector dist(n, vector<ld>(n+1));
    for(int i=0; i<n; i++) {
      rise[i] = 720 + real(a[i]) / 2000;
      rise[i] *= 60;
      for(int j=0; j<=n; j++) {
        dist[i][j] = abs(a[i] - a[j]) / v;
      }
    }

    int ans = 0;

    vector<ld> dp(1<<n, 1e42);
    dp[0] = 0;
    for(int bm=0; bm<1<<n; bm++) {
      if(dp[bm] > 1e41) continue;
      for(int i=0; i<n; i++) {
        if(bm & 1<<i) continue;

        // just i
        if(dp[bm] + dist[i][n] * 2 < rise[i]) {
          dp[bm | 1<<i] = min(dp[bm | 1<<i],
              dp[bm] + (dist[i][n] * 2 + dist[i][n]));
        }

        for(int j=0; j<i; j++) {
          if(bm & 1<<j) continue;

          // i then j
          if(dp[bm] + dist[i][n] * 4 < rise[i] &&
              dp[bm] + dist[i][n] * 4 + dist[i][j] * 2 < rise[j]) {
            dp[bm | 1<<i | 1<<j] = min(dp[bm | 1<<i | 1<<j],
                dp[bm] + (dist[i][n] * 4 + dist[i][j] * 2 + dist[j][n]));
          }

          // j then i
          if(dp[bm] + dist[j][n] * 4 < rise[j] &&
              dp[bm] + dist[j][n] * 4 + dist[j][i] * 2 < rise[i]) {
            dp[bm | 1<<i | 1<<j] = min(dp[bm | 1<<i | 1<<j],
                dp[bm] + (dist[j][n] * 4 + dist[j][i] * 2 + dist[i][n]));
          }
        }
      }

      if(dp[bm] < 1e41) {
        ans = max(ans, __builtin_popcount(bm));
      }
    }

    cout << ans << nl;
  }

  return 0;
}
