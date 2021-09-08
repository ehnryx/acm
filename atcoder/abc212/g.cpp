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

  ll n;
  cin >> n;

  vector<pair<ll, int>> pf;
  ll m = n - 1;
  for(ll d=2; d*d<=m; d++) {
    int cnt = 0;
    while(m % d == 0) {
      cnt += 1;
      m /= d;
    }
    if(cnt) {
      pf.emplace_back(d, cnt);
    }
  }
  if(m > 1) {
    pf.emplace_back(m, 1);
  }

  Int ans = 1;
  for(auto [p, c] : pf) {
    Int cur = 1;
    Int base = 1;
    for(int i=1; i<=c; i++) {
      cur += base * base * p * (p-1);
      base *= p;
    }
    ans *= cur;
  }
  cout << ans + 1 << nl;

  return 0;
}
