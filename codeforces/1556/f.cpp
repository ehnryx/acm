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
constexpr int MOD = 1e9+7;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

using Int = mod_int<MOD>;

const int N = 14;
int a[N];
Int scc[1<<N];
Int win[N][N];

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
  for(int i=0; i<n; i++) {
    cin >> a[i];
  }

  for(int i=0; i<n; i++) {
    for(int j=0; j<n; j++) {
      win[i][j] = Int(a[i]) / Int(a[i] + a[j]);
    }
  }

  Int ans = 0;
  for(int bm=1; bm<1<<n; bm++) {
    int cnt = __builtin_popcount(bm);
    scc[bm] = 1;
    for(int sm=(bm-1)&bm; sm; sm=(sm-1)&bm) {
      Int cut = 1;
      for(int i=0; i<n; i++) {
        if(!(sm & 1<<i)) continue;
        for(int j=0; j<n; j++) {
          if(!(bm & 1<<j)) continue;
          if(sm & 1<<j) continue;
          // i beats j
          cut *= win[i][j];
        }
      }
      scc[bm] -= scc[sm] * cut;
    }

    if(cnt == 1) assert(scc[bm] == 1);
    if(cnt == 2) assert(scc[bm] == 0);

    Int cur = 1;
    for(int i=0; i<n; i++) {
      if(!(bm & 1<<i)) continue;
      for(int j=0; j<n; j++) {
        if(bm & 1<<j) continue;
        // domination
        cur *= win[i][j];
      }
    }
    ans += scc[bm] * cur * cnt;
  }
  cout << ans << nl;

  return 0;
}
