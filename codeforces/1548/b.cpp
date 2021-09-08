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
  ll v;
  node(ll _v = 1): v(abs(_v)) {}
  ll get() const { return v; }
  void pull(const node& a, const node& b) { v = gcd(a.v, b.v); }
  void push(node&, node&) const {}
  static ll merge(ll a, ll b) { return gcd(a, b); }
  static ll default_value() { return 0; }
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

  int T;
  cin >> T;
  while(T--) {
    int n;
    cin >> n;
    vector<ll> a(n);
    for(int i=0; i<n; i++) {
      cin >> a[i];
    }

    vector<ll> diff;
    adjacent_difference(begin(a), end(a), back_inserter(diff));
    segment_tree<node, ll> st(diff);

    int ans = 1;
    for(int i=1, j=1; i<n; i++) {
      while(j <= i && st.query(j, i) == 1) {
        j++;
      }
      ans = max(ans, i-j + 2);
    }
    cout << ans << nl;
  }

  return 0;
}
