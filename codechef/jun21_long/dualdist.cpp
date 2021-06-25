#include <bits/stdc++.h>
using namespace std;

#include "../../../lca/tree/range_query_tree.h"
#include "../../../lca/data_structure/segment_tree.h"

const char nl = '\n';
using ll = long long;

struct node {
  ll value;
  int lazy, length;
  node() = default;
  void put(int v) {
    value += v * length;
    lazy += v;
  }
  ll get() const { return value; }
  void push(node& a, node& b) {
    if (lazy) {
      a.put(lazy);
      b.put(lazy);
      lazy = 0;
    }
  }
  void pull(const node& a, const node& b) {
    value = a.value + b.value;
  }
  static ll merge(ll a, ll b) { return a + b; }
  static ll default_value() { return 0; }
};

void solve(range_query_tree<segment_tree<node, ll>, ll>& tree,
           const vector<vector<tuple<int, int, int>>>& queries,
           int u, vector<ll>& ans) {
  for (int v : tree[u]) {
    tree.update_subtree(1, 1);
    tree.update_subtree(v, -2);
    //tree.update_subtree(v, -1);
    //tree.update_non_subtree(v, 1);
    solve(tree, queries, v, ans);
    tree.update_subtree(1, -1);
    tree.update_subtree(v, 2);
    //tree.update_subtree(v, 1);
    //tree.update_non_subtree(v, -1);
  }

  for (auto [umid, vmid, i] : queries[u]) {
    if (tree.parent[umid] == vmid) {
      ans[i] += tree.query_subtree(umid);
    } else {
      ans[i] += tree.query_non_subtree(vmid, node::merge);
    }
  }
}

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
    range_query_tree<segment_tree<node, ll>, ll> tree(adj, 1);

    vector<vector<tuple<int, int, int>>> queries(n + 1);
    for (int i = 0; i < m; i++) {
      int a, b;
      cin >> a >> b;
      int half = tree.distance(a, b) / 2;
      int amid = tree.kth(a, b, half);
      int bmid = tree.kth(a, b, half + 1);
      queries[a].emplace_back(amid, bmid, i);
      queries[b].emplace_back(bmid, amid, i);
    }

    tree.range_ds.assign_lengths();
    for (int i = 1; i <= n; i++) {
      tree.update_point(i, tree.depth[i]);
    }

    vector<ll> ans(m);
    solve(tree, queries, 1, ans);
    for(int i=0; i<m; i++) {
      cout << ans[i] << nl;
    }
  }

  return 0;
}