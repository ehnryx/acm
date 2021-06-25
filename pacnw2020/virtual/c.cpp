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

constexpr char nl = '\n';
constexpr ll INF = 0x3f3f3f3f;
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 998244353;
constexpr ld EPS = 1e-9L;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int N = 100 + 1;
char adj[N][N];
bool done[N][N];
bool vis[N][N][N];

// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#if defined(ONLINE_JUDGE) && defined(FILENAME)
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif

  int n, m, r, b, y;
  cin >> n >> m >> r >> b >> y;
  for(int i=0; i<m; i++) {
    int u, v; char c;
    cin >> u >> v >> c;
    adj[u][v] = adj[v][u] = c;
  }

  queue<tuple<int,int,int>> bfs;
  bfs.emplace(r, b, y);
  while(!bfs.empty()) {
    auto [i, j, k] = bfs.front();
    bfs.pop();
    if(vis[i][j][k]) continue;
    vis[i][j][k] = true;
    for(int v=1; v<=n; v++) {
      if(adj[i][v] == 'R' || adj[i][v] == 'X') {
        bfs.emplace(v, j, k);
        done[i][v] = done[v][i] = true;
      }
      if(adj[j][v] == 'B' || adj[j][v] == 'X') {
        bfs.emplace(i, v, k);
        done[j][v] = done[v][j] = true;
      }
      if(adj[k][v] == 'Y' || adj[k][v] == 'X') {
        bfs.emplace(i, j, v);
        done[k][v] = done[v][k] = true;
      }
      if(adj[i][v] == 'O' && i == k) {
        bfs.emplace(v, j, v);
        done[i][v] = done[v][i] = true;
      }
      if(adj[j][v] == 'G' && j == k) {
        bfs.emplace(i, v, v);
        done[j][v] = done[v][j] = true;
      }
      if(adj[j][v] == 'P' && i == j) {
        bfs.emplace(v, v, k);
        done[j][v] = done[v][j] = true;
      }
    }
  }

  bool ok = true;
  for(int i=1; i<=n; i++) {
    for(int j=1; j<=n; j++) {
      ok &= (!adj[i][j] || adj[i][j] == 'X' || done[i][j]);
    }
  }
  cout << ok << nl;

  return 0;
}
