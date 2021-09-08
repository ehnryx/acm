#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include "../../../lca/tree/range_query_tree.h"
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
  int value; bool lazy;
  node() = default;
  void put(int v) { value = v; lazy = true; }
  int get() const { return value; }
  void push(node& a, node& b) {
    if (lazy) {
      a.put(value);
      b.put(value);
      lazy = false;
    }
  }
  void pull(const node&, const node&) const {}
};
using DS = segment_tree<node, int>;

ll sqr(int x) { return (ll)x*x; }

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

    vector<int> parent(n+1);
    vector<vector<int>> adj(n+1);
    for(int i=2; i<=n; i++) {
      cin >> parent[i];
      adj[parent[i]].push_back(i);
    }

    range_query_tree<DS, int> tree(move(adj), 1);
    vector<int> down(n+1), tail(n+1);

    vector<ll> ans(n+1);
    tree.update_point(1, 1);
    tail[1] = 1;
    ans[1] = 0;

    for(int i=2; i<=n; i++) {
      tree.update_point(i, i);
      tail[i] = i;
      ans[i] = ans[i-1];

      int head = i;
      while (head != 1) {
        int mid = parent[head];
        int top = tree.query_point(mid);
        if (tree.depth[i] <= tree.depth[tail[top]]) {
          break; // nothing to do
        }
        if (mid == tail[top]) {
          // attach to tail
          down[mid] = i;
          tail[top] = i;
          tree.update_point(i, top);
          ans[i] += sqr(tree.depth[i] - tree.depth[top]) - sqr(tree.depth[mid] - tree.depth[top]);
        } else {
          // switch tail
          ans[i] -= sqr(tree.depth[i] - tree.depth[head]) + sqr(tree.depth[tail[top]] - tree.depth[top]);
          ans[i] += sqr(tree.depth[i] - tree.depth[top]) + sqr(tree.depth[tail[top]] - tree.depth[down[mid]]);
          tree.update_path(tail[top], down[mid], true, down[mid]);
          tree.update_path(i, head, true, top);
          tail[down[mid]] = tail[top];
          tail[top] = i;
          down[mid] = head;
        }
        head = top; // update head
      }
    }

    for(int i=1; i<=n; i++) {
      cout << ans[i] << " ";
    }
    cout << nl;
  }

  return 0;
}
