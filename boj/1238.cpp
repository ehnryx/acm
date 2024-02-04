%:include "graph/dijkstra.h"
%:include "main.h"
SOLVE() {
  int n, m, s;
  cin >> n >> m >> s;
  graph_t<int> in(n + 1), out(n + 1);
  for (int i = 0; i < m; i++) {
    int a, b, c;
    cin >> a >> b >> c;
    in.add_arc(b, a, c);
    out.add_arc(a, b, c);
  }
  auto din = dijkstra(in, -1).run(s);
  auto dout = dijkstra(out, -1).run(s);
  int ans = 0;
  for (int i = 1; i <= n; i++) {
    ans = max(ans, din.dist[i] + dout.dist[i]);
  }
  cout << ans << nl;
}
