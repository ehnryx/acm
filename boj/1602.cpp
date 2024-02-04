%:include "graph/graph_matrix.h"
%:include "main.h"
SOLVE() {
  int n, m, q;
  cin >> n >> m >> q;
  vector<int> cost(n + 1);
  for (int i = 1; i <= n; i++) {
    cin >> cost[i];
  }

  vector<int> order(n + 1);
  iota(begin(order), end(order), 0);
  sort(begin(order) + 1, end(order), [&](int i, int j) { return cost[i] < cost[j]; });
  vector<int> remap(n + 1);
  for (int i = 1; i <= n; i++) {
    remap[order[i]] = i;
  }

  graph_t<int, graph_traits::ADJACENCY_MATRIX> g(n + 1);
  for (int i = 0; i < m; i++) {
    int a, b, c;
    cin >> a >> b >> c;
    g.add_edge(remap[a], remap[b], c);
  }

  //g.floyd_warshall();
  nd_array<int, 2> ans(n + 1, n + 1, g.inf);
  for (int k = 1; k <= n; k++) {
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) {
        if (g(i, k) == g.inf or g(k, j) == g.inf) continue;
        g(i, j) = min(g(i, j), g(i, k) + g(k, j));
      }
    }
    for (int i = 1; i <= k; i++) {
      for (int j = 1; j <= k; j++) {
        if (g(i, j) == g.inf) continue;
        ans(i, j) = min(ans(i, j), g(i, j) + cost[order[k]]);
      }
    }
  }

  while (q--) {
    int a, b;
    cin >> a >> b;
    int res = ans(remap[a], remap[b]);
    if (res == g.inf) {
      cout << -1 << nl;
    } else {
      cout << res << nl;
    }
  }
}
