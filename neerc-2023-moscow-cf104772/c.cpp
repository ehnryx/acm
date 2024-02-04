%:include "graph/two_sat.h"
%:include "utility/output.h"
%:include "utility/recursive.h"

#define MULTI_TEST
%:include "main.h"

SOLVE() {
  int n;
  cin >> n;
  vector<int> colour(2 * n + 1);
  vector<int> seen(n + 1);
  //static two_sat sat(0); sat.reset(2*n + 1);
  two_sat sat(2 * n + 1);
  for (int i = 1; i <= 2 * n; i++) {
    cin >> colour[i];
    if (seen[colour[i]]) {
      sat.iff(seen[colour[i]], true, i, false);
    } else {
      seen[colour[i]] = i;
    }
  }
  graph_t g(2 * n + 1);
  for (int i = 1; i < 2 * n; i++) {
    int a, b;
    cin >> a >> b;
    g.add_edge(a, b);
  }
  vector<int> sz(2 * n + 1);
  auto build = recursive([&](auto self, int u, int p) -> void {
    sz[u] = 1;
    for (auto const& e : g.adj[u]) {
      if (e.to == p) continue;
      self(e.to, u);
      sz[u] += sz[e.to];
    }
    if (p) {
      bool dir = (sz[u] < n);
      sat.implies(u, dir, p, dir);
    }
  });
  build(1, 0);
  if (!sat.solve()) {
    return void(cout << -1 << nl);
  }
  vector<int> ans;
  for (int i = 1; i <= 2 * n; i++) {
    if (sat[i]) ans.push_back(i);
  }
  assert(size(ans) == n);
  cout << ans << nl;
}
