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
  int v;
  node() = default;
  void put(int x) { v = x; }
  int get() const { return v; }
  void pull(const node& a, const node& b) { v = max(a.v, b.v); }
  static int merge(int a, int b) { return max(a, b); }
  static int default_value() { return 0; }
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
  vector<vector<int>> adj(n+1);
  for(int i=0; i<m; i++) {
    int a, b;
    cin >> a >> b;
    adj[a].push_back(b);
  }

  segment_tree<node, int, false> st(n+1);
  for(int i=1; i<=n; i++) {
    sort(begin(adj[i]), end(adj[i]), greater<>());
    for(int j : adj[i]) {
      int best = st.query(0, j-1);
      st.update_point(j, best + 1);
    }
  }

  cout << st.query(0, n) << nl;

  return 0;
}
