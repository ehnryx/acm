#include <bits/stdc++.h>
using namespace std;

const char nl = '\n';

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;

const ll INF = 0x3f3f3f3f;

void print(int x, int y, const vector<string>& grid) {
  for (int i = 0; i < grid.size(); i++) {
    for (int j = 0; j < grid[i].size(); j++) {
      if (tie(i, j) == tie(x, y)) cerr << "*";
      else cerr << grid[i][j];
    }
    cerr << endl;
  }
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);

  int T; cin >> T;
  while (T--) {
    int r, c; cin >> r >> c;
    auto get = [&](int x, int y) {
      return x*c + y;
    };
    vector<vector<int>> adj(r*c);
    vector<string> grid(4*r + 3);
    getline(cin, grid[0]);
    for (int i = 0; i < 4*r + 3; i++) {
      getline(cin, grid[i]);
    }
    // find S, T
    int S, T;
    for (int i = 0; i < r; i++) {
      for (int j = 0; j < c; j++) {
        // center of hex
        int x, y;
        if (j % 2) {
          x = 4 * i + 4;
          y = 6 * j + 4;
        } else {
          x = 4 * i + 2;
          y = 6 * j + 4;
        }
        if (grid[x][y] == 'S') S = get(i, j);
        if (grid[x][y] == 'T') T = get(i, j);
      }
    }
    // top edges
    for (int i = 1; i < r; i++) {
      for (int j = 0; j < c; j++) {
        int x, y;
        if (j % 2) {
          x = 4 * i + 2;
          y = 6 * j + 4;
        } else {
          x = 4 * i;
          y = 6 * j + 4;
        }
        if (grid[x][y] == ' ') {
          adj[get(i, j)].push_back(get(i-1, j));
          adj[get(i-1, j)].push_back(get(i, j));
        }
      }
    }
    // top left edges
    for (int i = 0; i < r; i++) {
      for (int j = 1; j < c; j++) {
        int x, y;
        if (j % 2) {
          x = 4 * i + 3;
          y = 6 * j + 1;
          if (grid[x][y] == ' ') {
            adj[get(i, j)].push_back(get(i, j-1));
            adj[get(i, j-1)].push_back(get(i, j));
          }
        } else {
          x = 4 * i + 1;
          y = 6 * j + 1;
          if (grid[x][y] == ' ') {
            adj[get(i, j)].push_back(get(i-1, j-1));
            adj[get(i-1, j-1)].push_back(get(i, j));
          }
        }
      }
    }
    // top right edges
    for (int i = 0; i < r; i++) {
      for (int j = 0; j < c-1; j++) {
        int x, y;
        if (j % 2) {
          x = 4 * i + 3;
          y = 6 * j + 7;
          if (grid[x][y] == ' ') {
            adj[get(i, j)].push_back(get(i, j+1));
            adj[get(i, j+1)].push_back(get(i, j));
          }
        } else {
          x = 4 * i + 1;
          y = 6 * j + 7;
          if (grid[x][y] == ' ') {
            adj[get(i, j)].push_back(get(i-1, j+1));
            adj[get(i-1, j+1)].push_back(get(i, j));
          }
        }
      }
    }
    // aaaaaa
    vector<int> d(r*c, INF);
    d[S] = 0;
    queue<int> q;
    q.push(S);
    while (!q.empty()) {
      int u = q.front(); q.pop();
      for (int i : adj[u]) {
        if (d[i] > d[u] + 1) {
          d[i] = d[u] + 1;
          q.push(i);
        }
      }
    }
    cout << (d[T] == INF ? -1 : d[T]+1) << nl;
  }

  return 0;
}
