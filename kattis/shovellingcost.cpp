#include <bits/stdc++.h>
using namespace std;

%:include "io/fast_input.h"
%:include "graph/graph.h"
%:include "graph/breadth_first.h"

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

  for(int n, m; cin >> m >> n && n && m; ) {
    function<int(int,int)> get = [m](int i, int j) {
      return i*(m+2) + j;
    };

    auto g = cin.readinit<char, 1, 1>(n, m, '#');
    int nodes = (n+2) * (m+2);
    graph_list<int> graph(nodes);
    array<int, 4> loc;
    for(int i=1; i<=n; i++) {
      for(int j=1; j<=m; j++) {
        if(g[i][j] == '.' || isalpha(g[i][j])) {
          for(auto [di, dj] : { pair(0, 1), pair(1, 0), pair(-1, 0), pair(0, -1) }) {
            int ni = i + di;
            int nj = j + dj;
            graph.add_arc(get(i, j), get(ni, nj), g[ni][nj] == 'o');
          }
          if('A' <= g[i][j] && g[i][j] <= 'D') {
            loc[g[i][j] - 'A'] = get(i, j);
          }
        }
      }
    }

    int ans = numeric_limits<int>::max();
    vector<breadth_first<decltype(graph)>> bfs;
    for(int i=0; i<nodes; i++) {
      bfs.emplace_back(graph, i, true);
      for(int j=0; j<=i; j++) {
        if(bfs[i].dist[j] == -1) continue;
        for(int bm=0; bm<1<<4; bm++) {
          bool ok = true;
          int sum = 0;
          for(int k=0; k<4; k++) {
            if(bm & 1<<k) {
              ok &= (bfs[i].dist[loc[k]] != -1);
              sum += bfs[i].dist[loc[k]];
            } else {
              ok &= (bfs[j].dist[loc[k]] != -1);
              sum += bfs[j].dist[loc[k]];
            }
          }
          if(!ok) continue;
          sum += bfs[i].dist[j];
          sum += (g[i/(m+2)][i%(m+2)] == 'o');
          ans = min(ans, sum);
        }
      }
    }

    cout << ans << nl;
  }

  return 0;
}
