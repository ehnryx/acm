#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#ifdef HENRYX
#include "../../../lca/data_structure/segment_tree.h"
#else
#include "segment_tree.h"
#endif

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

struct Node {
  ll v;
  Node(): v(INFLL) {}
  ll get() const { return v; }
  void put(ll x) { v = min(v, x); }
  void pull(const Node& a, const Node& b) {}
  static ll merge(ll a, ll b) { return min(a, b); }
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

  int n, x, t;
  cin >> n >> x >> t;
  vector<int> h(n+1), d(n+1);
  vector<pair<int,int>> order;
  for(int i=1; i<=n; i++) {
    cin >> h[i];
    order.emplace_back(h[i], i);
  }
  for(int i=1; i<=n; i++) {
    cin >> d[i];
  }

  segment_tree<Node, ll, false> st(n);
  sort(begin(order), end(order));
  vector<int> remap(n+1);
  for(int i=0; i<n; i++) {
    remap[order[i].second] = i;
  }

  for(int i=1; i<=n; i++) {
    if(h[i] == h[x]) {
      st.update(remap[i], remap[i], i == x ? 0 : t);
    }
  }
  for(int i=0; i<n; i++) {
    int j = order[i].second;
    int ub = order[i].first + d[j];
    int r = upper_bound(begin(order), end(order), pair(ub, (int)INF)) - begin(order);
    int l = upper_bound(begin(order), end(order), pair(order[i].first, (int)INF)) - begin(order);
    st.update(l, r - 1, st.query_up(i) + t);
  }
  ll ans = st.query_up(remap[1]);
  if(ans < INFLL) {
    cout << ans << nl;
  } else {
    cout << -1 << nl;
  }

  return 0;
}
