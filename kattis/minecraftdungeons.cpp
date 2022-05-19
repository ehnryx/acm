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

  int n, m, radius;
  cin >> n >> m >> radius;
  auto g = cin.readinit<char, 1, 1>(n, m, 'X');

  int nodes = n*m * n*m + 2;
  graph_list<void> graph(nodes, true);
  const int source = n*m * n*m;
  const int sink = source + 1;

  function<int(int, int, int, int)> get = [=](int i, int j, int ii, int jj) {
    return (i-1) * (m * n*m) + (j-1) * (n*m) + (ii-1) * (m) + (jj-1);
  };

  function<int(int, int, int, int)> dist = [](int i, int j, int ii, int jj) {
    return max(abs(i - ii), abs(j - jj));
  };

  function<pair<int, int>(int, int, int, int)> creep = [=](int i, int j, int ii, int jj) {
    int nii = i < ii ? ii - 1 : i > ii ? ii + 1 : ii;
    int njj = j < jj ? jj - 1 : j > jj ? jj + 1 : jj;
    if(g[nii][jj] == 'X' && g[ii][njj] == 'X') return pair(ii, jj);
    if(g[nii][jj] == 'X') return pair(ii, njj);
    if(g[ii][njj] == 'X') return pair(nii, jj);
    return abs(i - ii) >= abs(j - jj) ? pair(nii, jj) : pair(ii, njj);
  };

  for(int i=1; i<=n; i++) {
    for(int j=1; j<=m; j++) {
      if(g[i][j] == 'X') continue;
      for(int ii=1; ii<=n; ii++) {
        for(int jj=1; jj<=m; jj++) {
          if(g[ii][jj] == 'X') continue;
          if(dist(i, j, ii, jj) <= radius) continue;
          int u = get(i, j, ii, jj);
          if(g[i][j] == 'P' && g[ii][jj] == 'C') {
            graph.add_edge(source, u); // start
          }
          if(g[i][j] == 'E') {
            graph.add_edge(u, sink); // end
          }
          auto [nii, njj] = creep(i, j, ii, jj);
          for(auto [di, dj] : {
              pair(0, 1), pair(1, 0), pair(0, -1), pair(-1, 0), pair(0, 0),
              }) {
            int ni = i + di;
            int nj = j + dj;
            if(g[ni][nj] == 'X') continue;
            graph.add_edge(u, get(ni, nj, nii, njj));
          }
        }
      }
    }
  }

  breadth_first bfs(graph, source);
  if(int ans = bfs.dist[sink]; ans == -1) {
    cout << "you're toast" << nl;
  } else {
    cout << ans - 2 << nl;
  }

  return 0;
}
