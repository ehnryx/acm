%:include <bits/stdc++.h>
using namespace std;

#include "../../../lca/misc/fast_input.h"

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int INF = 0x3f3f3f3f;
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());


int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);

  fast_input cin;

  int T;
  cin >> T;
  while(T--) {
    int n, k;
    cin >> n >> k;
    vector<int> a(n+1);
    for(int i=1; i<=n; i++) {
      cin >> a[i];
    }
    vector dp(n+1, 0);
    for(int i=1; i<=n; i++) {
      if(a[i] > i) continue;
      dp[i] = 1;
      for(int j=1; j<i; j++) {
        if(a[j] < a[i] && a[i] - a[j] <= i - j) {
          dp[i] = max(dp[i], dp[j] + 1);
        }
      }
    }
    int ans = n+1;
    for(int i=1; i<=n; i++) {
      if(dp[i] >= k) {
        ans = min(ans, i - a[i]);
      }
    }
    if(ans > n) {
      cout << -1 << nl;
    } else {
      cout << ans << nl;
    }
  }

  return 0;
}
