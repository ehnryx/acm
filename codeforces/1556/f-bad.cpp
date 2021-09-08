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

Int invalid;

const int N = 14;
int a[N];
Int dp[N][1<<N];
Int win[N][N], rev[N][N];
Int lose[N][1<<N]; // lose to all in the group

Int solve(int u, int bm) {
  if(dp[u][bm] != invalid) return dp[u][bm];
  if(bm == 0) return dp[u][bm] = 1;

  Int res = 0;
  int lsb = bm & -bm;
  for(int sm = bm ^ lsb; ; sm = (sm - 1) & (bm ^ lsb)) {
    int group = sm | lsb;
    // now the group needs to lose against everyone else
    Int sad = 1;
    for(int i=0; i<N; i++) {
      if(group & 1<<i) {
        sad *= lose[i][bm ^ group];
      }
    }
    Int lost = 1;
    for(int i=0; i<N; i++) {
      if(group & 1<<i) {
        Int p_group = solve(i, group ^ 1<<i);
        Int win_group = lost * win[u][i];
        // win_group * p_group is probability of winning the group
        res += sad * win_group * p_group * solve(u, bm ^ group);
        lost *= Int(1) - solve(i, group ^ 1<<i);
      }
    }
    if(sm == 0) break;
  }

  return dp[u][bm] = res;
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

  invalid.v = -1;
  fill(&dp[0][0], &dp[0][0] + N*(1<<N), invalid);

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

  for(int i=0; i<n; i++) {
    for(int j=0; j<n; j++) {
      rev[i][j] = win[i][j] / win[j][i];
    }
  }

  for(int i=0; i<n; i++) {
    for(int bm=0; bm<1<<n; bm++) {
      if(bm & 1<<i) continue;
      lose[i][bm] = 1;
      for(int j=0; j<N; j++) {
        if(bm & 1<<j) {
          lose[i][bm] *= win[j][i]; // sad
        }
      }
    }
  }

  const int mask = (1<<n) - 1;
  Int ans = 0;
  for(int i=0; i<n; i++) {
    ans += solve(i, mask ^ 1<<i);
  }
  cout << ans << nl;

  return 0;
}
