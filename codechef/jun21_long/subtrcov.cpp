#include <bits/stdc++.h>
using namespace std;

#include "../../../lca/tree/range_query_tree.h"
#include "../../../lca/data_structure/segment_tree.h"

const char nl = '\n';
using ll = long long;

struct node {
  int value;
  int lazy;
  node() = default;
  int get() const { return value; }
  void put(int v) { value += v; lazy += v; }
  void pull(const node& a, const node& b) {
    value = max(a.value, b.value);
  }
  void push(node& a, node& b) {
    if (lazy) {
      a.put(lazy);
      b.put(lazy);
      lazy = 0;
    }
  }
  bool contains(int v) { return value >= v; }
  static int merge(int a, int b) { return max(a, b); }
  static int default_value() { assert(false); }
};
using RMQ = segment_tree<node, int>;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;
  while (T--) {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n + 1);
    for (int i = 1; i < n; i++) {
      int a, b;
      cin >> a >> b;
      adj[a].push_back(b);
      adj[b].push_back(a);
    }

    vector<bool> vis(n + 1);
    queue<int> bfs;
    bfs.push(1);
    vis[1] = true;
    int root = -1;
    while (!empty(bfs)) {
      int u = bfs.front();
      bfs.pop();
      root = u;
      for (int v : adj[u]) {
        if (!vis[v]) {
          vis[v] = true;
          bfs.push(v);
        }
      }
    }
    assert(root != -1);

    range_query_tree<segment_tree<node, int>, int> hld(adj, root);
    assert(hld.depth[root] == 0);
    for (int i = 1; i <= n; i++) {
      hld.update_point(i, hld.depth[i]);
    }

    int ans = 1;
    m -= 1;
    vector<bool> done(n + 1);
    done[root] = true;
    while (m > 0) {
      int add = hld.query_subtree(root);
      int u = hld.search_subtree(root, add);
      while (!done[u]) {
        hld.update_subtree(u, -1);
        done[u] = true;
        u = hld.parent[u];
      }
      ans += 1;
      m -= add;
    }

    cout << ans << nl;
  }

  return 0;
}