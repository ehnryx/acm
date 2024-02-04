%:include "graph/graph_matrix.h"
%:include "main.h"
struct gmt : graph_matrix_traits_base<int> {
  static constexpr bool self_zero = false;
};
SOLVE() {
  int n, m;
  cin >> n >> m;
  graph_t<int, graph_traits::ADJACENCY_MATRIX, gmt> graph(n + 1);
  for (int i = 0; i < m; i++) {
    int a, b, c;
    cin >> a >> b >> c;
    graph.add_arc(a, b, c);
  }
  graph.floyd_warshall();
  int ans = graph.inf;
  for (int i = 1; i <= n; i++) {
    ans = min(ans, graph(i, i));
  }
  if (ans == graph.inf) {
    cout << -1 << nl;
  } else {
    cout << ans << nl;
  }
}
