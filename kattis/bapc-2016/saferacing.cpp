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
constexpr ll MOD = 123456789;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());



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

  int n, k;
  cin >> n >> k;
  vector<ll> dp(n+1);
  dp[0] = 1;
  ll window = 1;
  for(int i=1; i<=n; i++) {
    dp[i] = window;
    window += dp[i];
    if(i-k >= 0) window -= dp[i-k];
    while(window < 0) window += MOD;
    while(window >= MOD) window -= MOD;
  }
  ll ans = 0;
  for(int i=1; i<=k; i++) {
    ans = (ans + i * dp[n-i]) % MOD;
  }
  cout << ans << nl;

  return 0;
}
