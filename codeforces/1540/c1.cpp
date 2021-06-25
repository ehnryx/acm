#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include "../../../lca/number/mod_int.h"

//#define FILENAME sadcactus

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int INF = 0x3f3f3f3f;
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;
constexpr int MOD = 1e9 + 7;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

using Int = mod_int<MOD>;

// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#if defined(ONLINE_JUDGE) && defined(FILENAME)
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif

  int n;
  cin >> n;
  vector<int> c(n+1), b(n+1);
  for(int i=1; i<=n; i++) {
    cin >> c[i];
  }
  for(int i=1; i<=n-1; i++) {
    cin >> b[i];
  }

  vector<int> sum(n+1);
  partial_sum(begin(c), end(c), begin(sum));

  vector<int> prefix(n+1);
  for(int k=1; k<=n; k++) {
    for(int j=1; j<k; j++) {
      prefix[k] += b[j] * (k - j);
    }
  }

  int m;
  cin >> m;
  assert(m == 1);

  int x;
  cin >> x;
  vector dp(n+1, vector<Int>(sum.back() + 1));
  dp[0][0] = 1;
  for(int i=1; i<=n; i++) {
    for(int s=0; s<=sum[i]; s++) {
      if(s - prefix[i] < i * x) continue;
      for(int v=0; v<=min(s,c[i]); v++) {
        dp[i][s] += dp[i-1][s-v];
      }
    }
  }

  Int ans = accumulate(begin(dp[n]), end(dp[n]), Int(0));
  cout << ans << nl;

  return 0;
}
