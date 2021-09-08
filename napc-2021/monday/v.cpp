#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include "../../../lca/data_structure/segment_tree.h"
#include "../../../lca/tree/range_query_tree.h"

//#define FILENAME sadcactus

/*
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
template <typename T>
using ordered_set = __gnu_pbds::tree<T,
      __gnu_pbds::null_type,
      less<T>,
      __gnu_pbds::rb_tree_tag,
      __gnu_pbds::tree_order_statistics_node_update>;
      */

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
  node(): v(0) {}
  void put(int add) { v += add; }
  int get() const { return v; }
  void pull(const node& a, const node& b) {
    v = a.v + b.v;
  }
  static int merge(int a, int b) { return a + b; }
  static int default_value() { assert(false); }
};
using segtree = segment_tree<node, int, false>;

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
  for(int i=1; i<n; i++) {
    int a, b;
    cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }
  range_query_tree<segtree, int> tree(adj, 1);

  vector<bool> bad(n+1);
  for(int i=0; i<m; i++) {
    int t;
    cin >> t;
    if(t == 1) {
      int v;
      cin >> v;
      bad[v] = !bad[v];
      if(tree.parent[v] != -1) {
        if(bad[v]) {
          tree.update_point(tree.parent[v], 1);
        } else {
          tree.update_point(tree.parent[v], -1);
        }
      }
    } else {
      int a, b;
      cin >> a >> b;
      int res = tree.query_path(a, b, true, 0, node::merge);
      int c = tree.lca(a, b);
      res += bad[c];
      res += (tree.parent[c] != -1 && bad[tree.parent[c]]);
      cout << res << nl;
    }
  }

  return 0;
}
