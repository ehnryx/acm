#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>
using namespace std;

// 14:11 -> 14:26 -> 14:32

#define FILENAME "labyrinth"

#define nl '\n'
typedef long long ll;
typedef long double ld;

vector<int> dx = { 0, 0, 1, 1, 1, -1, -1, -1 };
vector<int> dy = { 1, -1, 0, 1, -1, 0, 1, -1 };

const int N = 1500 + 9;
const int O = 3;
const int INF = 0x3f3f3f3f;

char g[N][N];
int topright[N][N], botleft[N][N], obstacles[N][N];

void traverse(int ss, int tt, int vis[N][N]) {
  queue<pair<int,int>> bfs;
  bfs.emplace(ss, tt);
  vis[ss][tt] = true;
  while(!bfs.empty()) {
    auto [x, y] = bfs.front();
    bfs.pop();
    for(int d=0; d<8; d++) {
      int nx = x + dx[d];
      int ny = y + dy[d];
      if(g[nx][ny] != '#' || vis[nx][ny]) continue;
      vis[nx][ny] = true;
      bfs.emplace(nx, ny);
    }
  }
}

void gen_sums(int a[N][N]) {
  for(int i=1; i<N; i++) {
    for(int j=1; j<N; j++) {
      a[i][j] += a[i-1][j] + a[i][j-1] - a[i-1][j-1];
    }
  }
}

int get_sum(int a[N][N], int l, int r, int x, int y) {
  return a[r][y] + a[l-1][x-1] - a[r][x-1] - a[l-1][y];
}

bool valid(int i, int j, int r, bool check=false) {
  return get_sum(botleft, i-r, i+1, j-r, j+1)
      && get_sum(topright, i-r, i+1, j-r, j+1)
      && (!check || !get_sum(obstacles, i-r+1, i, j-r+1, j));
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
#ifdef ONLINE_JUDGE
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif

  int n, m;
  cin >> n >> m;
  swap(n, m);
  for(int i=1; i<=n; i++) {
    for(int j=1; j<=m; j++) {
      cin >> g[O+i][O+j];
      obstacles[O+i][O+j] = (g[O+i][O+j] == '#');
    }
  }
  for(int i=2; i<=n; i++) {
    g[O+i][O+0] = '#';
  }
  for(int j=0; j<m; j++) {
    g[O+n+1][O+j] = '#';
  }
  for(int j=2; j<=m; j++) {
    g[O+0][O+j] = '#';
  }
  for(int i=0; i<n; i++) {
    g[O+i][O+m+1] = '#';
  }

  traverse(O+n+1, O, botleft);
  traverse(O, O+m+1, topright);

  gen_sums(botleft);
  gen_sums(topright);

  obstacles[O+1][O+1] = 1;
  obstacles[O+n][O+m] = 1;
  gen_sums(obstacles);

  tuple<int,int,int> best(INF, -1, -1);
  for(int i=1; i<=n; i++) {
    for(int j=1; j<=m; j++) {
      int l = 1;
      int r = min(i, j);
      while(l < r) {
        int mid = (l+r) / 2;
        if(valid(O+i, O+j, mid)) {
          r = mid;
        } else {
          l = mid + 1;
        }
      }
      if(valid(O+i, O+j, r, true)) {
        best = min(best, make_tuple(r, i-r+1, j-r+1));
      }
    }
  }

  auto [r, i, j] = best;
  if(r == INF) {
    cout << "Impossible" << nl;
  } else {
    cout << r << " " << j << " " << i << nl;
  }

  return 0;
}
