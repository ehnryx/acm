%:include "graph/graph_matrix.h"
//%:include "utility/nd_array.h"
%:include "main.h"
struct gmt : graph_matrix_traits_base<int> {};
SOLVE() {
  int n, m;
  cin >> n >> m;
  vector<tuple<int, int, int>> edges;
  for (int bs = 0; bs < 500; bs++) {
    constexpr auto big = numeric_limits<int>::max();
    graph_t<int, graph_traits::ADJACENCY_MATRIX, gmt> adj(n + 1);
    //nd_array<int, 2> adj(n + 1, n + 1, big);
    //vector adj(n + 1, vector(n + 1, big));
    for (int i = 0; i < m; i++) {
      int a, b, c;
      if (bs == 0) {
        cin >> a >> b >> c;
        edges.emplace_back(a, b, c);
      } else {
        tie(a, b, c) = edges[i];
      }
      adj.add_arc(a, b, c);
      //adj(a, b) = min(adj(a, b), c);
      //adj[a][b] = min(adj[a][b], c);
    }
    adj.floyd_warshall(1);
    //for (int k = 1; k <= n; k++) {
    //  adj(k, k) = 0;
    //  //adj[k][k] = 0;
    //  for (int i = 1; i <= n; i++) {
    //    for (int j = 1; j <= n; j++) {
    //      if (adj(i, k) == big or adj(k, j) == big) continue;
    //      adj(i, j) = min(adj(i, j), adj(i, k) + adj(k, j));
    //      //if (adj[i][k] == big or adj[k][j] == big) continue;
    //      //adj[i][j] = min(adj[i][j], adj[i][k] + adj[k][j]);
    //    }
    //  }
    //}
    if (bs == 0) {
      for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
          if (adj(i, j) == big) adj(i, j) = 0;
          cout << adj(i, j) << " ";
          //if (adj[i][j] == big) adj[i][j] = 0;
          //cout << adj[i][j] << " ";
        }
        cout << nl;
      }
    }
  }
}
