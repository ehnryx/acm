#include <bits/stdc++.h>
using namespace std;

constexpr char nl = '\n';

const int INF = 0x3f3f3f3f;

const vector<int> dx = {0, 0, 1, 1, 1, -1, -1, -1};
const vector<int> dy = {1, -1, 0, 1, -1, 0, 1, -1};

struct Item {
  int x, y, h;
  Item(int _x, int _y, int _h): x(_x), y(_y), h(_h) {}
  bool operator < (const Item& o) const {
    return h > o.h; // smallest first
  }
};

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int n, m;
  cin >> n >> m;
  vector grid(n+2, vector<int>(m+2, INF));
  for(int i=1; i<=n; i++) {
    for(int j=1; j<=m; j++) {
      cin >> grid[i][j];
    }
  }
  int tx, ty;
  cin >> tx >> ty;

  long long ans = 0;
  vector vis(n+2, vector<bool>(m+2, false));
  priority_queue<Item> dijk;
  dijk.emplace(tx, ty, grid[tx][ty]);
  while(!dijk.empty()) {
    auto [x, y, h] = dijk.top();
    dijk.pop();
    if(vis[x][y]) continue;
    if(h < 0) ans += -h;
    vis[x][y] = true;
    for(int d=0; d<8; d++) {
      int nx = x + dx[d];
      int ny = y + dy[d];
      if(grid[nx][ny] < INF && !vis[nx][ny]) {
        dijk.emplace(nx, ny, max(grid[nx][ny], h));
      }
    }
  }
  cout << ans << nl;

  return 0;
}
