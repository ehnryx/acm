%:include "graph/graph_matrix.h"
%:include "main.h"
SOLVE() {
  int n, m;
  cin >> n >> m;
  graph_t<void, graph_traits::ADJACENCY_MATRIX, graph_matrix_traits_base<void>> g(n + 1);
  for (int i = 0; i < m; i++) {
    int a, b;
    cin >> a >> b;
    g.add_edge(a, b);
  }
  g.floyd_warshall();
  vector<int> res(n + 1);
  vector<int> maxd(n + 1);
  for (int i = 1; i <= n; i++) {
    for (auto [_, d] : g[i]) {
      maxd[i] = max(maxd[i], d);
    }
    int j = (*g[i].begin()).to;
    if (not res[j] or maxd[i] < maxd[res[j]]) {
      res[j] = i;
    }
  }
  vector<int> ans;
  for (int i = 1; i <= n; i++) {
    if (res[i]) {
      ans.push_back(res[i]);
    }
  }
  sort(begin(ans), end(ans));
  cout << size(ans) << nl;
  for (int it : ans) {
    cout << it << nl;
  }
}
