#include <bits/stdc++.h>
using namespace std;

//%:include "io/fast_input.h"

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

  int n, m;
  cin >> n >> m;
  vector g(n+2, vector<char>(m+2, 'X'));

  queue<pair<int, int>> bfs, ffs;
  vector flood(n+2, vector<unsigned>(m+2, -1));
  vector dist(n+2, vector<unsigned>(m+2, -1));
  pair<int, int> den;

  for(int i=1; i<=n; i++) {
    for(int j=1; j<=m; j++) {
      cin >> g[i][j];
      if(g[i][j] == '*') {
        ffs.emplace(i, j);
        flood[i][j] = 0;
      } else if(g[i][j] == 'S') {
        bfs.emplace(i, j);
        dist[i][j] = 0;
      } else if(g[i][j] == 'D') {
        den = pair(i, j);
      }
    }
  }

  auto trans = {
    pair(0, 1), pair(1, 0), pair(-1, 0), pair(0, -1),
  };

  while(!empty(ffs)) {
    auto [i, j] = ffs.front();
    ffs.pop();
    for(auto [di, dj] : trans) {
      int ni = i + di;
      int nj = j + dj;
      if(g[ni][nj] == 'X' || g[ni][nj] == 'D' || flood[ni][nj] != -1) continue;
      flood[ni][nj] = flood[i][j] + 1;
      ffs.emplace(ni, nj);
    }
  }

  while(!empty(bfs)) {
    auto [i, j] = bfs.front();
    bfs.pop();
    for(auto [di, dj] : trans) {
      int ni = i + di;
      int nj = j + dj;
      if(g[ni][nj] == 'X' || dist[ni][nj] != -1) continue;
      if(dist[i][j] + 1 < flood[ni][nj]) {
        dist[ni][nj] = dist[i][j] + 1;
        bfs.emplace(ni, nj);
      }
    }
  }

  if(dist[den.first][den.second] == -1) {
    cout << "KAKTUS" << nl;
  } else {
    cout << dist[den.first][den.second] << nl;
  }

  return 0;
}
