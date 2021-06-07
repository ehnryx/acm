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

typedef long long ll;
typedef long double ld;
typedef complex<ld> pt;

constexpr char nl = '\n';
constexpr ll INF = 0x3f3f3f3f;
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

using Int = mod_int<998244353>;
//using Int = long double;

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

  int n, m;
  cin >> n >> m;
  vector dist(m, vector<int>(n));
  for(int i=0; i<n; i++) {
    for(int j=0; j<m; j++) {
      cin >> dist[j][i];
    }
  }

  Int ans(0);
  for(int i=0; i<m; i++) {
    sort(begin(dist[i]), end(dist[i]), greater<>());
    Int alive(1);
    for(int j=0, s=0; j<n; j++) {
      while(s < n && dist[i][s] > n-j) s++;
      Int cur = Int(n-s) / (n-j) * alive;
      ans += cur;
      alive -= cur;
    }
  }
  cout << ans << nl;

  return 0;
}
