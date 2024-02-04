%:include "graph/bellman_ford.h"
%:include "graph/graph.h"
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

  //static int constexpr inf = numeric_limits<int>::max();
  static int constexpr inf = numeric_limits<int>::min();
  // either works

  bellman_ford bf(g, 1, inf);
  vector<int> ans(n + 1, -1);
  for (int i = 1; i <= n; i++) {
    if (bf.get_dists()[i] == inf) continue;
    if (bf.in_negative_cycle(i)) {
      return void(cout << -1 << nl);
    }
    ans[i] = bf.get_dists()[i];
  }

  for (int i = 2; i <= n; i++) {
    cout << ans[i] << nl;
  }
}
