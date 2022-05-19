#include <bits/stdc++.h>
using namespace std;

%:include "io/fast_input.h"

//%:include "graph/graph.h"
////%:include "graph/dijkstra.h"
//%:include "graph/breadth_first.h"

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());


int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#ifdef USING_FAST_INPUT
  fast_input cin;
#endif

  for(int n, m; cin >> n >> m && n; ) {
    auto g = cin.readinit<char, 1, 1>(n, m, '#');
    g[0][0] = g[0][1] = g[1][0] = '@';
    g[n+1][m+1] = g[n][m+1] = g[n+1][m] = '@';

    int nodes = (n+2) * (m+2);
    function<int(int, int)> get = [&](int i, int j) {
      return i*(m+2) + j;
    };

    /*
    graph_list<int> graph(nodes, true);
    for(int i=0; i<=n+1; i++) {
      for(int j=0; j<=m+1; j++) {
        if(g[i][j] == '@') continue;
        int u = get(i, j);
        for(int di=-1; di<=1; di++) {
          for(int dj=-1; dj<=1; dj++) {
            if(di == 0 && dj == 0) continue;
            if(i+di < 0 || i+di > n+1) continue;
            if(j+dj < 0 || j+dj > m+1) continue;
            if(g[i+di][j+dj] == '@') continue;
            int v = get(i+di, j+dj);
            graph.add_edge(u, v, g[i+di][j+dj] == '.');
          }
        }
      }
    }
    breadth_first ans(graph, get(0, m+1), true);
    cout << ans.dist[get(n+1, 0)] << nl;
    */

    deque<int> bfs;
    bfs.push_back(get(0, m+1));
    vector<int> dist(nodes, -1);
    dist[get(0, m+1)] = 0;

    while(!empty(bfs)) {
      int u = bfs.front();
      bfs.pop_front();
      int i = u / (m+2);
      int j = u % (m+2);
      for(int di=-1; di<=1; di++) {
        for(int dj=-1; dj<=1; dj++) {
          if(di == 0 && dj == 0) continue;
          if(i+di < 0 || i+di > n+1) continue;
          if(j+dj < 0 || j+dj > m+1) continue;
          if(g[i+di][j+dj] == '@') continue;
          int v = get(i+di, j+dj);
          if(dist[v] != -1) continue;
          if(g[i+di][j+dj] == '.') {
            dist[v] = dist[u] + 1;
            bfs.push_back(v);
          } else {
            dist[v] = dist[u];
            bfs.push_front(v);
          }
        }
      }
    }

    cout << dist[get(n+1, 0)] << nl;
  }

  return 0;
}
