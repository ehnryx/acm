#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
//%:include "utility/output.h"

using ll = long long;
using ld = long double;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());


//#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  int n, m;
  cin >> n >> m;
  vector g(n+2, vector(m+2, -1));
  for(int i=1; i<=n; i++) {
    for(int j=1; j<=m; j++) {
      cin >> g[i][j];
    }
  }

  const int N = (n+2) * (m+2);
  auto get = [m](int i, int j) {
    return i * (m+2) + j;
  };

  static constexpr auto transitions = {
    pair(0, 1), pair(1, 0), pair(-1, 0), pair(0, -1) };

  auto go = [&](int i, int j, int v) {
    pair to(0, 0);
    for(auto [di, dj] : transitions) {
      int ni = i + di;
      int nj = j + dj;
      if(g[ni][nj] == -1) continue;
      if(g[to.first][to.second] == -1 or
          abs(g[ni][nj] - v) < abs(g[to.first][to.second] - v) or
          (abs(g[ni][nj] - v) == abs(g[to.first][to.second] - v) and
           abs(g[ni][nj] - g[i][j]) < abs(g[to.first][to.second] - g[i][j]))) {
        to = pair(ni, nj);
      }
    }
    return to;
  };

  auto build = [&](int x, int y) {
    vector<int> dist(N, -1);
    queue<pair<int, int>> bfs;
    dist[get(x, y)] = 0;
    bfs.emplace(x, y);
    while(not empty(bfs)) {
      auto [i, j] = bfs.front();
      bfs.pop();
      for(auto [di, dj] : {
          pair(0, 1), pair(1, 0), pair(-1, 0), pair(0, -1) }) {
        int ni = i + di;
        int nj = j + dj;
        if(g[ni][nj] == -1 or dist[get(ni, nj)] != -1) continue;
        if(go(ni, nj, g[x][y]) == pair(i, j)) {
          dist[get(ni, nj)] = dist[get(i, j)] + 1;
          bfs.emplace(ni, nj);
        }
      }
    }
    return dist;
  };

  vector<vector<int>> dist(N);
  for(int x=1; x<=n; x++) {
    for(int y=1; y<=m; y++) {
      dist[get(x, y)] = build(x, y);
    }
  }

  auto solve = [&](int x, int y) {
    int res = 0;
    for(int i=1; i<=n; i++) {
      for(int j=1; j<=m; j++) {
        if(int u = dist[get(i, j)][get(x, y)]; u == -1) {
          return -1;
        } else {
          res = max(res, u);
        }
      }
    }
    return res;
  };

  pair ans(-1, -1);
  for(int x=1; x<=n; x++) {
    for(int y=1; y<=m; y++) {
      auto cur = solve(x, y);
      if(cur == -1) continue;
      if(ans.first == -1 or cur < ans.first) {
        ans = pair(cur, g[x][y]);
      }
    }
  }
  if(ans.first == -1) {
    cout << "impossible" << nl;
  } else {
    cout << ans.second << " " << ans.first << nl;
  }
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#ifdef USING_FAST_INPUT
  fast_input cin;
#endif

  int T = 1;
#ifdef MULTI_TEST
  cin >> T;
#endif
  for(int testnum=1; testnum<=T; testnum++) {
    solve_main(testnum, cin);
  }

  return 0;
}
