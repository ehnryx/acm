#include <map>
%:include "tree/range_query_tree.h"
%:include "ds/segment_tree.h"
%:include "ds/segment_tree_nodes_min.h"
#define MULTI_TEST
%:include "main.h"

using node = segment_tree_nodes::range_add_range_min<int, std::greater<int>>;

SOLVE() {
  int n;
  cin >> n;
  vector<vector<int>> adj(n+1);
  for(int i=2; i<=n; i++) {
    int parent;
    cin >> parent;
    adj[parent].push_back(i);
  }
  range_query_tree<segment_tree<node>> g(std::move(adj), 1);

  vector<int> vals(n+1);
  for(int i=1; i<=n; i++) {
    cin >> vals[i];
    if(g[i].empty()) {
      g.update_subtree(i, 1);
    }
  }

  vector<vector<int>> next_vals(n+1);
  vector<vector<int>> seen(n+1);
  auto build = [&](auto& self, int u) -> void {
    if(not empty(seen[vals[u]])) {
      next_vals[seen[vals[u]].back()].push_back(u);
    }
    seen[vals[u]].push_back(u);
    for(int v : g[u]) {
      self(self, v);
    }
    seen[vals[u]].pop_back();
  };
  build(build, g.root);

  vector<int> lens(n+1, 0);

  auto update = [&](int u, vector<int> const& nbs, int i) {
    g.update_subtree(u, 1);
    while(i < size(nbs) and g.index(nbs[i]) <= g.subtree_end(u)) {
      g.update_subtree(nbs[i], -1);
      i++;
    }
    lens[u] = g.query_subtree(u);
    return i;
  };

  ll ans = 0;
  auto solve = [&](auto& self, int u) -> void {
    int maxl = 1;
    int second = 1;
    int nid = 0;
    for(int v : g[u]) {
      self(self, v);
      nid = update(v, next_vals[u], nid);
      //cerr << v << " <- " << u << " : " << lens[v] << nl;
      if(lens[v] > maxl) {
        second = maxl;
        maxl = lens[v];
      } else if(lens[v] > second) {
        second = lens[v];
      }
    }
    ans = max(ans, (ll)maxl * second);
    lens[u] = maxl;
  };

  solve(solve, g.root);

  cout << ans << nl;
  assert(ans);
}
