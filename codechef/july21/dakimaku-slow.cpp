//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2")

#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include "../../../lca/number/capped_int.h"

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

using Int = capped_int<INF>;

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

  int T;
  cin >> T;
  while(T--) {
    int n, cap;
    cin >> n >> cap;
    vector<int> a(n+1);
    for(int i=1; i<=n; i++) {
      cin >> a[i];
    }
    ll total = accumulate(begin(a), end(a), (ll)0);
    vector<ll> d(n+1);
    for(int i=2; i<=n; i++) {
      cin >> d[i];
    }
    partial_sum(begin(d), end(d), begin(d));

    ll l = 0;
    ll r = 1e12;
    while (l < r) {
      ll m = (l+r) / 2;

      vector<Int> dp(n+1, INF);
      dp[0] = 0;
      for(int i=1; i<=n; i++) {
        for(int j=1; j<=i; j++) {
          // block [j .. i]
          vector<pair<ll, int>> order; // pair(time, cnt);
          for(int k=i; k>=j; k--) {
            if(a[k] == 0) continue;
            order.emplace_back(d[i] - d[k], a[k]);
          }
          if(empty(order)) {
            dp[i] = min(dp[i], dp[j-1]);
            continue;
          }
          if(order.back().first >= m) {
            continue; // too late
          }

          // find best amount
          ll lx = 1;
          ll rx = total;
          while (lx < rx) {
            ll mx = (lx + rx) / 2; // productivity mx
            ll lastt = 0;
            ll have = 0;
            for(auto [t, c] : order) {
              ll dt = t - lastt;
              lastt = t;
              if (have / mx + 1 < dt) { // avoid overflow
                have = 0;
              } else {
                have = max((ll)0, have - dt * mx);
              }
              have += c;
            }
            // last time block
            lastt = m - lastt;
            assert(lastt > 0);
            ll need = (have + lastt - 1) / lastt;
            if (need <= mx) {
              rx = mx; // good, keep productivity
            } else {
              lx = mx + 1;
            }
          }
          dp[i] = min(dp[i], dp[j-1] + rx);
        }
      }

      if(dp[n] <= cap) {
        r = m;
      } else {
        l = m+1;
      }
    }

    cout << r << nl;
  }

  return 0;
}
