%:include "graph/graph_matrix.h"
%:include "geometry/point.h"
struct gmt : graph_matrix_traits_base<int> {};
#define MULTI_TEST
%:include "main.h"
SOLVE() {
  int n;
  cin >> n;
  vector<point<int>> p(n + 2);
  for (int i = 0; i < n + 2; i++) {
    cin >> p[i];
  }
  graph_t<int, graph_traits::ADJACENCY_MATRIX, gmt> g(n + 2);
  for (int i = 0; i < n + 2; i++) {
    for (int j = 0; j < i; j++) {
      if (int dist = manhattan(p[i] - p[j]); dist <= 50 * 20) {
        g.add_edge(i, j, dist);
      }
    }
  }
  g.floyd_warshall();
  if (g(0, n + 1) == g.inf) {
    cout << "sad" << nl;
  } else {
    cout << "happy" << nl;
  }
}
