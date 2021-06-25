#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include "../../lca/number/mod_int.h"

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
  vector<int> a(m);
  vector<bool> have(n+1);
  for(int i=0; i<m; i++) {
    cin >> a[i];
    have[a[i]] = true;
  }

  vector<int> pref(m+1);
  for(int i=0; i<m; i++) {
    pref[i+1] = max(pref[i], a[i]);
  }

  Int ans = 1;
  int add = 0;
  for(int i=1; i<=n; i++) {
    if(have[i]) continue;
    auto it = lower_bound(begin(pref), end(pref), i);
    if(it == end(pref)) {
      ans *= m + add + 1;
    } else {
      ans *= int(it - begin(pref)) + add - 1;
    }
    add++;
  }
  cout << ans << nl;

  return 0;
}
