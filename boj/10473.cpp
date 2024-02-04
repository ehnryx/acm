%:include "graph/graph_matrix.h"
%:include "geometry/point.h"
%:include "main.h"
using gmt = graph_matrix_traits_base<double>;
SOLVE() {
  point<double> source, sink;
  cin >> source >> sink;
  int n;
  cin >> n;
  vector<point<double>> p(n);
  for (int i = 0; i < n; i++) {
    cin >> p[i];
  }

  graph_t<double, graph_traits::ADJACENCY_MATRIX, gmt> graph(n + 2);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      auto dist = abs(p[i] - p[j]);
      dist = min(dist / 5, abs(dist - 50) / 5 + 2);
      graph.add_arc(i, j, dist);
    }
  }
  for (int i = 0; i < n; i++) {
    {
      auto dist = abs(p[i] - source);
      dist = dist / 5;
      graph.add_arc(n, i, dist);
    }
    {
      auto dist = abs(p[i] - sink);
      dist = min(dist / 5, abs(dist - 50) / 5 + 2);
      graph.add_arc(i, n + 1, dist);
    }
  }
  graph.add_arc(n, n + 1, abs(source - sink) / 5);

  //for (auto [a, b, c] : graph.get_edges()) {
  //  cerr << a << " -> " << b << " | " << c << endl;
  //}

  graph.floyd_warshall();
  cout << graph(n, n + 1) << nl;
}
