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

const vector<int> dx = { 0, 0, 1, -1 };
const vector<int> dy = { 1, -1, 0, 0 };

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
  vector grid(n+2, vector<char>(m+2, '#'));
  pair<int,int> source, sink;
  for(int i=1; i<=n; i++) {
    for(int j=1; j<=m; j++) {
      cin >> grid[i][j];
      if(grid[i][j] == 'R') {
        source = pair(i, j);
      } else if(grid[i][j] == 'E') {
        sink = pair(i, j);
      }
    }
  }
  string com;
  cin >> com;
  int len = com.size();

  vector dp(n+2, vector(m+2, vector<int>(len+1, -1)));
  deque<tuple<int,int,int,int>> bfs;
  bfs.emplace_back(source.first, source.second, 0, 0);
  while(!bfs.empty()) {
    auto [x, y, p, dist] = bfs.front();
    bfs.pop_front();
    if(x == sink.first && y == sink.second) {
      cout << dist << nl;
      return 0;
    }
    if(dp[x][y][p] != -1) continue;
    dp[x][y][p] = dist;
    // follow
    if(p < len) {
      int nx, ny;
      if(com[p] == 'U') tie(nx, ny) = pair(x-1, y);
      else if(com[p] == 'D') tie(nx, ny) = pair(x+1, y);
      else if(com[p] == 'L') tie(nx, ny) = pair(x, y-1);
      else tie(nx, ny) = pair(x, y+1);
      if(grid[nx][ny] == '#') tie(nx, ny) = pair(x, y);
      if(dp[nx][ny][p+1] == -1) {
        bfs.emplace_front(nx, ny, p+1, dist);
      }
    }
    // delete
    if(p < len && dp[x][y][p+1] == -1) {
      bfs.emplace_back(x, y, p+1, dist + 1);
    }
    // insert
    for(int d=0; d<4; d++) {
      int nx = x + dx[d];
      int ny = y + dy[d];
      if(grid[nx][ny] != '#' && dp[nx][ny][p] == -1) {
        bfs.emplace_back(nx, ny, p, dist + 1);
      }
    }
  }
  assert(false);

  return 0;
}
