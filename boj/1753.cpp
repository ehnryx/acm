%:include "graph/dijkstra.h"
%:include "main.h"
SOLVE() {
  int n, m;
  cin >> n >> m;
  int source;
  cin >> source;
  graph_t<int> g(n + 1);
  for (int i = 0; i < m; i++) {
    int a, b, c;
    cin >> a >> b >> c;
    g.add_arc(a, b, c);
  }
  auto d = dijkstra(g, -1).run(source).get_dists();
  for (int i = 1; i <= n; i++) {
    if (d[i] == -1) {
      cout << "INF" << nl;
    } else {
      cout << d[i] << nl;
    }
  }
}
