%:include "graph/dijkstra.h"
%:include "main.h"
SOLVE() {
  int n, m;
  cin >> n >> m;
  graph_t<int> g(n + 1);
  for (int i = 0; i < m; i++) {
    int a, b, c;
    cin >> a >> b >> c;
    g.add_arc(a, b, c);
  }
  int s, t;
  cin >> s >> t;
  cout << dijkstra(g, -1).run(s).get_dists()[t] << nl;
}
