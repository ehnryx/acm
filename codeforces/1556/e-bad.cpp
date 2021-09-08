#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include "../../../lca/data_structure/segment_tree.h"

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

struct node {
  ll big, small;
  node(ll v=0): big(v), small(v) {}
  const node& get() const { return *this; }
  const node& pull(const node& a, const node& b) {
    big = max(a.big, b.big);
    small = min(a.small, b.small);
    return *this;
  }
  static node merge(const node& a, const node& b) { return node().pull(a, b); }
  static node default_value() { assert(false); }
};

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
  vector<int> a(n), b(n);
  for(int i=0; i<n; i++) {
    cin >> a[i];
  }
  vector<ll> v(n+1);
  for(int i=0; i<n; i++) {
    cin >> b[i];
    v[i+1] = b[i] - a[i];
  }
  partial_sum(begin(v), end(v), begin(v));
  segment_tree<node, node, false> st(v);

  for(int i=0; i<m; i++) {
    int l, r;
    cin >> l >> r;
    auto [top, bot] = st.query(l, r);
    ll base = v[l-1];
    if(bot != base || top < base) {
      cout << -1 << nl;
    } else {
      cout << top - base << nl;
    }
  }

  return 0;
}
