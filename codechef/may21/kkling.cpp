#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include "../../../lca/data_structure/segment_tree.h"
#include "../../../lca/data_structure/union_find.h"
#include "../../../lca/tree/rooted_tree.h"

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

struct Sum {
  int value;
  Sum() = default;
  void put(int v) { value += v; }
  int get() const { return value; }
  void push(Sum&, Sum&) {}
  void pull(const Sum& a, const Sum& b) { value = a.value + b.value; }
  static int default_value() { return 0; }
  static int merge(int a, int b) { return a + b; }
};

struct Min {
  pair<int,int> value;
  Min(): value(INF, 0) {}
  void put(pair<int,int> v) { value = min(value, v); }
  pair<int,int> get() const { return value; }
  void push(Min&, Min&) {}
  void pull(const Min&, const Min&) {}
  static pair<int,int> merge(const pair<int,int>& a, const pair<int,int>& b) {
    return min(a, b);
  }
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
    vector<vector<int>> adj(n+1);
    for(int i=1; i<n; i++) {
      int a, b;
      cin >> a >> b;
      adj[a].push_back(b);
      adj[b].push_back(a);
    }
    rooted_tree g(adj, 1);
    union_find<false> dsu(n+1);

    vector<int> leaf;
    for(int i=1; i<=n; i++) {
      if(empty(g[i])) {
        leaf.push_back(i);
      }
    }

    segment_tree<Sum, int> sums(n+1);
    segment_tree<Min, pair<int,int>> mins(n+1);
    int iters = 0;
    for(;;) {
      iters++;
      for(int u : leaf) {
        if(g.parent[u] == 1) {
          dsu.link(u, 1);
        }
        sums.update_point(g.start[g.parent[u]], 1);
        int l = g.start[g.parent[u]];
        int r = l + g.subtree[g.parent[u]] - 1;
        mins.update(l, r, pair(g.depth[g.parent[u]], g.parent[u]));
      }
      assert(dsu[1] == 1);
      if(dsu.size[1] > 1) break;

      vector<int> alive;
      for(int u : leaf) {
        int v = g.parent[u];
        int l = g.start[v];
        int r = l + g.subtree[v] - 1;
        if(sums.query(l, r) == sums.query_point(g.start[v])) {
          alive.push_back(v);
          dsu.link(u, v);
          if(int to = mins.query_up(g.start[v]).second; to != v) {
            g.parent[v] = to;
          }
        }
      }

      for(int u : leaf) {
        sums.update_point(g.start[g.parent[u]], -1);
      }

      leaf.clear();
      leaf = move(alive);
      sort(begin(leaf), end(leaf));
      leaf.resize(unique(begin(leaf), end(leaf)) - begin(leaf));
      assert(!empty(leaf));
    }

    vector<int> ans;
    for(int i=1; i<=n; i++) {
      if(empty(g[i]) && dsu[i] == 1) {
        ans.push_back(i);
      }
    }
    cout << size(ans) << " " << iters << nl;
    for(int it : ans) {
      cout << it << " ";
    }
    cout << nl;
  }

  return 0;
}
