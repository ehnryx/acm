#include <bits/stdc++.h>
using namespace std;


const char nl = '\n';
using ll = long long;
using ld = long double;


int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, m, r, b, y;
  cin >> n >> m >> r >> b >> y;

  vector<vector<pair<int, char>>> adj(n + 1);
  vector painted(n + 1, vector<bool>(n + 1));

  int goal = 0;
  for (int i = 0; i < m; i++) {
    int u, v; char c;
    cin >> u >> v >> c;
    adj[u].emplace_back(v, c);
    adj[v].emplace_back(u, c);
    goal += (c != 'X');
  }

  queue<tuple<int, int, int>> bfs;
  vector vis(n + 1, vector(n + 1, vector<bool>(n + 1)));
  vis[r][b][y] = true;
  bfs.emplace(r, b, y);

  while (!empty(bfs)) {
    auto [ru, bu, yu] = bfs.front();
    bfs.pop();

    // move red
    for (auto [v, c] : adj[ru]) {
      if (c != 'R' && c != 'X') continue;
      painted[ru][v] = (c == 'R');
      if (!vis[v][bu][yu]) {
        vis[v][bu][yu] = true;
        bfs.emplace(v, bu, yu);
      }
    }

    // move blue
    for (auto [v, c] : adj[bu]) {
      if (c != 'B' && c != 'X') continue;
      painted[bu][v] = (c == 'B');
      if (!vis[ru][v][yu]) {
        vis[ru][v][yu] = true;
        bfs.emplace(ru, v, yu);
      }
    }

    // move yellow
    for (auto [v, c] : adj[yu]) {
      if (c != 'Y' && c != 'X') continue;
      painted[yu][v] = (c == 'Y');
      if (!vis[ru][bu][v]) {
        vis[ru][bu][v] = true;
        bfs.emplace(ru, bu, v);
      }
    }

    // move red + blue = purple
    if (ru == bu) {
      for (auto [v, c] : adj[ru]) {
        if (c != 'P' && c != 'X') continue;
        painted[ru][v] = (c == 'P');
        if (!vis[v][v][yu]) {
          vis[v][v][yu] = true;
          bfs.emplace(v, v, yu);
        }
      }
    }

    // move blue + yellow = green
    if (bu == yu) {
      for (auto [v, c] : adj[bu]) {
        if (c != 'G' && c != 'X') continue;
        painted[bu][v] = (c == 'G');
        if (!vis[ru][v][v]) {
          vis[ru][v][v] = true;
          bfs.emplace(ru, v, v);
        }
      }
    }

    // move yellow + red = orange
    if (yu == ru) {
      for (auto [v, c] : adj[yu]) {
        if (c != 'O' && c != 'X') continue;
        painted[yu][v] = (c == 'O');
        if (!vis[v][bu][v]) {
          vis[v][bu][v] = true;
          bfs.emplace(v, bu, v);
        }
      }
    }
  }

  int have = 0;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      have += painted[i][j];
    }
  }
  assert(have % 2 == 0);
  if (have / 2 == goal) {
    cout << 1 << nl;
  } else {
    cout << 0 << nl;
  }

  return 0;
}
