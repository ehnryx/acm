%:include "graph/graph_matrix.h"
%:include "main.h"
struct update_if {
  int operator()(int a, int b) const { return (a == 0 or b < a) ? b : a; }
};
struct gmt : graph_matrix_traits_base<void> {
  static constexpr bool self_zero = false;
  static constexpr int inf = 0;
  using edge_update_t = update_if;
};
SOLVE() {
  int n;
  cin >> n;
  graph_t<void, graph_traits::ADJACENCY_MATRIX, gmt> g(n);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cin >> g(i, j);
    }
  }
  g.floyd_warshall();
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cout << !!g(i, j) << " ";
    }
    cout << nl;
  }
}
