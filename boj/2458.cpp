%:include "graph/graph_matrix.h"
%:include "main.h"
SOLVE() {
  int n, m;
  cin >> n >> m;
  graph_t<void, graph_traits::ADJACENCY_MATRIX> g(n + 1);
  for (int i = 0; i < m; i++) {
    int a, b;
    cin >> a >> b;
    g.add_arc(a, b);
  }
  g.floyd_warshall();
  int ans = 0;
  for (int i = 1; i <= n; i++) {
    int cnt = 0;
    for (int j = 1; j <= n; j++) {
      cnt += (g(i, j) != g.inf or g(j, i) != g.inf);
    }
    ans += (cnt == n);
  }
  cout << ans << nl;
}
