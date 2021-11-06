#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

enum {
  north, south, west, east, up, down,
};

vector<tuple<int, int, int>> transitions = {
  tuple(north, -1, 0),
  tuple(south, 1, 0),
  tuple(west, 0, -1),
  tuple(east, 0, 1),
};

int rotate(int d, int dir) {
  if(d == dir) return down;
  if(d == down) return dir^1;
  if(d == (dir^1)) return up;
  if(d == up) return dir;
  return d;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);

  int T;
  cin >> T;
  while(T--) {
    int n;
    cin >> n;
    vector g(n+2, vector<char>(n+2, '*'));
    pair<int, int> source, sink;
    for(int i=1; i<=n; i++) {
      for(int j=1; j<=n; j++) {
        cin >> g[i][j];
        if(g[i][j] == 'S') {
          source = pair(i, j);
        } else if(g[i][j] == 'H') {
          sink = pair(i, j);
        }
      }
    }

    vector vis(n+2, vector(n+2, vector<bool>(6)));
    vis[source.first][source.second][west] = true;
    queue<tuple<int, int, int>> bfs;
    bfs.emplace(source.first, source.second, west);
    while(!empty(bfs)) {
      auto [i, j, dir] = bfs.front();
      bfs.pop();
      for (auto [rot, di, dj] : transitions) {
        int ni = i + di;
        int nj = j + dj;
        int nd = rotate(dir, rot);
        if(g[ni][nj] != '*' && !vis[ni][nj][nd]) {
          vis[ni][nj][nd] = true;
          bfs.emplace(ni, nj, nd);
        }
      }
    }

    if(vis[sink.first][sink.second][down]) {
      cout << "Yes" << nl;
    } else {
      cout << "No" << nl;
    }
  }

  return 0;
}
