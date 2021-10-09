#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

//#define FILENAME sadcactus

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
template <typename T>
using ordered_set = __gnu_pbds::tree<T,
      __gnu_pbds::null_type,
      less<T>,
      __gnu_pbds::rb_tree_tag,
      __gnu_pbds::tree_order_statistics_node_update>;

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int INF = 0x3f3f3f3f;
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;
constexpr int MOD = 1e9 + 7;
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

  int n, k, m;
  cin >> n >> k >> m;
  k = min(k, m/2);
  k = min(k, n-1);

  ll ans = 0;
  vector dyck(m+1, vector<int>(k+1));
  dyck[0][0] = 1;
  for(int i=1; i<=m; i++) {
    for(int j=0; j<=k; j++) {
      if(j > 0) dyck[i][j] += dyck[i-1][j-1];
      if(j + 1 <= k) dyck[i][j] += dyck[i-1][j+1];
      if(dyck[i][j] >= MOD) dyck[i][j] -= MOD;
    }
    ans += dyck[i][0];
  }

  ans = (ans % MOD * 2*n) % MOD;
  cout << ans << nl;

  return 0;
}
