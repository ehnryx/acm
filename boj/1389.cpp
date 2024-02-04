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
  int best = numeric_limits<int>::max();
  int ans = -1;
  for (int i = 1; i <= n; i++) {
    int cur = 0;
    for (auto [_, c] : g[i]) {
      cur += c;
    }
    if (cur < best) {
      best = cur;
      ans = i;
    }
  }
  assert(ans != -1);
  cout << ans << nl;
}
