#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

//#define FILENAME sadcactus

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;
typedef long double ld;
typedef complex<ld> pt;

constexpr char nl = '\n';
constexpr ll INF = 0x3f3f3f3f;
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

bool valid(int l, int r, int lim) {
  if(l % 10 * 10 + r % 10 >= lim) return false;
  if(l % 10 * 10 + r / 10 >= lim) return false;
  return true;
}

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
  vector<int> lim(n+1, 1);
  for(int i=1; i<=n; i++) {
    cin >> lim[i];
  }

  // position, error?, value
  vector dp(n+1, vector(2, vector<ll>(100)));
  dp[0][0][0] = 1;
  for(int i=1; i<=n; i++) {
    for(int j=0; j<lim[i]; j++) {
      for(int v=0; v<lim[i-1]; v++) {
        if(valid(v, j, lim[i])) {
          dp[i][0][j] += dp[i-1][0][v];
          dp[i][1][j] += dp[i-1][1][v];
        } else {
          dp[i][1][j] += dp[i-1][0][v];
          dp[i][1][j] += dp[i-1][1][v];
        }
      }
    }
  }
  ll ans = accumulate(begin(dp[n][1]), end(dp[n][1]), (ll)0);
  cout << ans << nl;

  return 0;
}
