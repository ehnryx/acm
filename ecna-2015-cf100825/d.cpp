//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

//#define FILENAME sadcactus

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;
typedef long double ld;
typedef complex<ld> pt;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 998244353;
const ld EPS = 1e-9;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const vector<int> dx = { 1, -1, 0, 0 };
const vector<int> dy = { 0, 0, 1, -1 };

const int N = 100 + 2;
char g[N][N];
bool vis[N][N];
int dist[N][N];

// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);
#if defined(ONLINE_JUDGE) && defined(FILENAME)
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif

  int n, m;
  cin >> n >> m;
  for(int i=1; i<=n; i++) {
    for(int j=1; j<=m; j++) {
      cin >> g[i][j];
      if(g[i][j] == '.') g[i][j] = 0;
    }
  }

  queue<pair<int,int>> bfs;
  for(int i=0; i<=n+1; i++) {
    for(int j=0; j<=m+1; j++) {
      if(!g[i][j]) {
        bfs.emplace(i, j);
        vis[i][j] = true;
      }
    }
  }

  int mad = 0;
  while(!bfs.empty()) {
    auto [x, y] = bfs.front();
    bfs.pop();
    mad = max(mad, dist[x][y]);
    for(int d=0; d<4; d++) {
      int nx = x + dx[d];
      int ny = y + dy[d];
      if(nx > 0 && nx <= n && ny > 0 && ny <= m && !vis[nx][ny]) {
        vis[nx][ny] = true;
        dist[nx][ny] = dist[x][y] + 1;
        bfs.emplace(nx, ny);
      }
    }
  }

  int len = (mad < 10 ? 2 : 3);
  for(int i=1; i<=n; i++) {
    for(int j=1; j<=m; j++) {
      if(dist[i][j]) {
        cout << setw(len) << setfill('.') << dist[i][j];
      } else {
        cout << setw(len) << setfill('.') << '.';
      }
    }
    cout << nl;
  }

  return 0;
}
