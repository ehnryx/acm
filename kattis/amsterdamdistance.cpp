#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

struct Edge {
  int x, y; ld dist;
  bool operator < (const Edge& o) const {
    return dist > o.dist;
  }
};

const int N = 1e2+3;
vector<Edge> adj[N][N];
ld dist[N][N];

//#define FILEIO
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);
#ifdef FILEIO
  freopen("test.in", "r", stdin);
  freopen("test.out", "w", stdout);
#endif

  fill(&dist[0][0], &dist[0][0]+N*N, -7);

  int m, n; ld r;
  cin >> m >> n >> r;

  for (int i=0; i<=m; i++) {
    for (int j=0; j<=n; j++) {
      if (i>0) {
        adj[i][j].push_back({i-1, j, j*r/n * M_PIl/m});
        adj[i-1][j].push_back({i, j, j*r/n * M_PIl/m});
      }
      if (j>0) {
        adj[i][j].push_back({i, j-1, r/n});
        adj[i][j-1].push_back({i, j, r/n});
      }
    }
  }

  int sx, sy, tx, ty;
  cin >> sx >> sy >> tx >> ty;
  priority_queue<Edge> dijk;
  dijk.push({sx,sy,0});
  while (!dijk.empty()) {
    Edge cur = dijk.top();
    dijk.pop();
    if (dist[cur.x][cur.y] < -1) {
      dist[cur.x][cur.y] = cur.dist;
      if (cur.x==tx && cur.y==ty) break;
      for (const Edge& e : adj[cur.x][cur.y]) {
        dijk.push({e.x, e.y, e.dist+cur.dist});
      }
    }
  }
  cout << dist[tx][ty] << nl;

  return 0;
}
