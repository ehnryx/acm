#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include "../../../lca/number/mod_int.h"

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
constexpr int MOD = 998244353;
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

  int n, m;
  cin >> n >> m;

  vector<Int> fact(n+1);
  fact[0] = 1;
  for(int i=1; i<=n; i++) {
    fact[i] = fact[i-1] * i;
  }

  vector ncr(n+1, vector<Int>(n+1));
  for(int i=0; i<=n; i++) {
    ncr[i][i] = ncr[i][0] = 1;
    for(int j=1; j<i; j++) {
      ncr[i][j] = ncr[i-1][j] + ncr[i-1][j-1];
    }
  }

  vector<Int> overcnt(n+1);
  for(int i=1; i<=n; i++) {
    overcnt[i] = 1;
    for(int r=1; r<=m; r++) {
      int put = (n-r) / m + 1;
      if(put > i) {
        overcnt[i] = 0;
        break;
      } else {
        overcnt[i] *= ncr[i][put] * fact[put];
      }
    }
  }

  for(int i=1; i<=n; i++) {
    Int res = 0;
    for(int j=0; j<=i; j++) {
      Int cur = ncr[i][j] * overcnt[i-j];
      if(j % 2 == 0) {
        res += cur;
      } else {
        res -= cur;
      }
    }
    cout << res / fact[i] << nl;
  }

  return 0;
}
