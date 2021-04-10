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
random_device _rd; mt19937 rng(_rd());

const vector<pair<int,int>> dirs = {
  {0, 1}, {0, -1}, {1, 0}, {-1, 0}, {0, 0},
};

pair<int,int> read_pair() {
  string x, y;
  cin >> x >> y;
  y.pop_back();
  return pair(stoi(x.substr(1)), stoi(y));
}

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

  int n, m;
  cin >> n >> m;
  pair<int,int> source = read_pair();
  pair<int,int> sink = read_pair();

  vector g(n+2, vector<char>(m+2, '#'));
  for(int i=1; i<=n; i++) {
    for(int j=1; j<=m; j++) {
      cin >> g[i][j];
    }
  }

  int p;
  cin >> p;
  vector<vector<pair<int,int>>> paths(p);
  int period = 1;
  for(int i=0; i<p; i++) {
    int k;
    cin >> k;
    for(int j=0; j<k; j++) {
      paths[i].push_back(read_pair());
    }
    if(paths[i].size() > 1) {
      vector<pair<int,int>> rev(next(rbegin(paths[i])), prev(rend(paths[i])));
      paths[i].insert(end(paths[i]), begin(rev), end(rev));
    }
    period = lcm(period, size(paths[i]));
  }
  cerr << "period: " << period << nl;

  vector bad(period, vector(n+2, vector<bool>(m+2)));
  for(int t=0; t<period; t++) {
    for(const auto& path : paths) {
      auto [x, y] = path[t % path.size()];
      for(int d : {-1, 1}) {
        for(int i=x; g[i][y] != '#'; i+=d) {
          bad[t][i][y] = true;
        }
        for(int j=y; g[x][j] != '#'; j+=d) {
          bad[t][x][j] = true;
        }
      }
    }
  }

  function<int(int,int,int)> get = [=](int t, int i, int j) {
    return (i-1)*m + (j-1) + t*n*m;
  };

  int goal = period * n * m;
  vector<vector<int>> adj(goal + 1);
  for(int t=0; t<period; t++) {
    int nt = t+1 < period ? t+1 : 0;
    for(int i=1; i<=n; i++) {
      for(int j=1; j<=m; j++) {
        if(bad[t][i][j] || g[i][j] == '#') continue;
        for(auto [di, dj] : dirs) {
          int ni = i + di;
          int nj = j + dj;
          if(g[ni][nj] == '#') continue;
          adj[get(t, i, j)].push_back(get(nt, ni, nj));
        }
      }
    }
    adj[get(t, sink.first, sink.second)].push_back(goal);
  }

  vector<int> dist(goal + 1, -1);
  queue<int> bfs;
  int start = get(0, source.first, source.second);
  bfs.push(start);
  dist[start] = 0;
  while(!bfs.empty()) {
    int u = bfs.front();
    bfs.pop();
    for(int v : adj[u]) {
      if(dist[v] != -1) continue;
      bfs.push(v);
      dist[v] = dist[u] + 1;
    }
  }

  if(dist[goal] < 0) {
    cout << "IMPOSSIBLE" << nl;
  } else {
    cout << dist[goal] - 1 << nl;
  }

  return 0;
}
