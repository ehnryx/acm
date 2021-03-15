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

void solve() {
  static const vector<int> dx = {-1, 1, 0, 0};
  static const vector<int> dy = {0, 0, -1, 1};

  int n, m, q;
  cin >> n >> m >> q;

  function<int(int,int)> get = [=](int i, int j) {
    return m * (i-1) + (j-1);
  };

  vector grid(n+2, vector<char>(m+2, '#'));
  pair<int,int> s;
  vector<pair<int,int>> lift;
  for(int i=1; i<=n; i++) {
    for(int j=1; j<=m; j++) {
      cin >> grid[i][j];
      if(grid[i][j] == 'E') {
        s = pair(i, j);
      } else if(grid[i][j] == '?') {
        lift.emplace_back(i, j);
      }
    }
  }

  vector<vector<int>> adj(n*m);
  vector<bool> impossible(n*m);
  int tot = lift.size();
  for(int bm=0; bm<1<<tot; bm++) {
    for(int i=0; i<tot; i++) {
      if(bm & 1<<i) {
        grid[lift[i].first][lift[i].second] = '#';
      } else {
        grid[lift[i].first][lift[i].second] = '.';
      }
    }

    vector dist(n+2, vector<int>(m+2, -1));
    queue<pair<int,int>> bfs;
    bfs.push(s);
    dist[s.first][s.second] = 0;
    while(!bfs.empty()) {
      auto [i, j] = bfs.front();
      bfs.pop();
      for(int d=0; d<4; d++) {
        int ni = i + dx[d];
        int nj = j + dy[d];
        if(grid[ni][nj] == '#' || dist[ni][nj] != -1) continue;
        bfs.emplace(ni, nj);
        dist[ni][nj] = dist[i][j] + 1;
      }
    }

    for(int i=1; i<=n; i++) {
      for(int j=1; j<=m; j++) {
        if(dist[i][j] == 0 || grid[i][j] == '#') continue;
        if(dist[i][j] < 0) {
          impossible[get(i, j)] = true;
        } else {
          for(int d=0; d<4; d++) {
            int ni = i + dx[d];
            int nj = j + dy[d];
            if(dist[i][j] == dist[ni][nj] + 1) {
              adj[get(i, j)].push_back(get(ni, nj));
              break;
            }
          }
        }
      }
    }
  }
  assert(adj[get(s.first, s.second)].empty());

  vector<vector<int>> rev(n*m);
  vector<int> deg(n*m);
  for(int i=0; i<n*m; i++) {
    for(int j : adj[i]) {
      rev[j].push_back(i);
      deg[i]++;
    }
  }

  vector<int> dist(n*m, 0);
  vector<bool> vis(n*m);
  queue<int> bfs;
  bfs.push(get(s.first, s.second));
  while(!bfs.empty()) {
    int u = bfs.front();
    bfs.pop();
    vis[u] = true;
    for(int v : rev[u]) {
      dist[v] = max(dist[v], dist[u] + 1);
      if(--deg[v] == 0) {
        bfs.push(v);
      }
    }
  }

  for(int i=0; i<q; i++) {
    int x, y;
    cin >> x >> y;
    int u = get(x, y);
    if(vis[u] && !impossible[u]) {
      cout << dist[u] << nl;
    } else {
      cout << -1 << nl;
    }
  }
}

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

  int T;
  cin >> T;
  for(int tt=1; tt<=T; tt++) {
    cout << "Case " << tt << ":" << nl;
    solve();
  }

  return 0;
}
