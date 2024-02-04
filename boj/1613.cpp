%:include "main.h"
%:include "graph/graph_matrix.h"
SOLVE() {
  int n, m;
  cin >> n >> m;
  graph_t<void, graph_traits::ADJACENCY_MATRIX, graph_matrix_traits_base<void>> g(n + 1);
  for (int i = 0; i < m; i++) {
    int a, b;
    cin >> a >> b;
    g.add_arc(a, b);
  }
  g.floyd_warshall();
  int q;
  cin >> q;
  while (q--) {
    int a, b;
    cin >> a >> b;
    if (g(a, b) != g.inf) cout << -1 << nl;
    else if (g(b, a) != g.inf) cout << 1 << nl;
    else cout << 0 << nl;
  }
}
