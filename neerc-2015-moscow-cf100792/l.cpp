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

const int N = 500 + 17;
const int L = 1 << 12;
pair<int,int> nodes[N];
vector<int> tracks[N];
vector<pair<int,int>> rev[N];
vector<pair<int,int>> adj[N][L];
bool allowed[N][L];
int dist[N][L];

void build_paths(int s, int len) {
  for(int bm=0; bm<1<<(len-1); bm++) {
    vector<int> path = {nodes[s].first, nodes[s].second};
    for(int i=1, u=s; i<len; i++) {
      int j = bm >> (i-1) & 1;
      if(j >= tracks[u].size()) break;
      u = tracks[u][j];
      path.push_back(nodes[u].second);
    }
    sort(path.begin(), path.end());
    if(unique(path.begin(), path.end()) - path.begin() == len + 1) {
      allowed[s][bm] = true;
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

  int n, m, k;
  cin >> n >> m >> k;
  int len = max(1, (k-1) / 40);

  for(int i=1; i<=m; i++) {
    int a, b, c;
    cin >> a >> b >> c;
    nodes[i] = make_pair(a, b);
    for(int j=0; j<c; j++) {
      int v;
      cin >> v;
      if(b != n) {
        tracks[i].push_back(v);
        rev[v].emplace_back(i, j);
      }
    }
    if(b == n) {
      tracks[i].push_back(m+1);
      rev[m+1].emplace_back(i, 0);
    }
  }

  for(int i=1; i<=len; i++) {
    nodes[m+i] = make_pair(n+i-1, n+i);
    tracks[m+i].push_back(m+i+1);
    rev[m+i+1].emplace_back(m+i, 0);
  }

  for(int i=1; i<=m+1; i++) {
    build_paths(i, len);
  }

  const int mask = (1 << (len-1)) - 1;
  for(int i=1; i<=m+1; i++) {
    for(int bm=0; bm<1<<(len-1); bm++) {
      if(!allowed[i][bm]) continue;
      for(auto [j, t] : rev[i]) {
        int om = ((bm << 1) | t) & mask;
        if(!allowed[j][om]) continue;
        adj[i][bm].emplace_back(j, om);
      }
    }
  }

  memset(dist, -1, sizeof dist);
  queue<pair<int,int>> bfs;
  bfs.emplace(m+1, 0);
  dist[m+1][0] = 0;
  while(!bfs.empty()) {
    auto [u, bm] = bfs.front();
    bfs.pop();
    if(nodes[u].first == 1) {
      cout << dist[u][bm] * 1000 + k * 25 << nl;
      return 0;
    }
    for(auto [v, om] : adj[u][bm]) {
      if(dist[v][om] != -1) continue;
      dist[v][om] = dist[u][bm] + 1;
      bfs.emplace(v, om);
    }
  }

  cout << "No chance" << nl;

  return 0;
}
