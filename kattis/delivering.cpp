//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

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
const ll MOD = 1e9+7;
const ld EPS = 1e-13;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

namespace Flow {
  const int N = 2 * (300 + 1) + 2;
  struct Edge { int v, r; int f, c; };
  vector<Edge> adj[N]; int sz[N];
  void add_edge(int a, int b, int c=1) {
    adj[a].push_back({b,sz[b]++,0,c,});
    adj[b].push_back({a,sz[a]++,0,0,}); }
  int L[N], cur[N], Q[N];
  bool bfs(int s, int t) {
    memset(L, INF, sizeof L); memset(cur, 0, sizeof cur);
    int f,b; Q[f=b=0] = s; L[s] = 0;
    while(f<=b && L[t]==INF) { int u = Q[f++];
      for(const Edge& e:adj[u]) if(L[e.v] == INF && e.c > e.f) {
        Q[++b] = e.v; L[e.v] = L[u]+1; } } return L[t] < INF; }
  int dfs(int u, int t, int f) { if (u == t || !f) return f;
    for (int i = cur[u]; i < sz[u]; cur[u] = ++i) { Edge& e = adj[u][i];
      if(e.f<e.c && L[e.v]==L[u]+1) {
        if(int cf = dfs(e.v, t, min(e.c-e.f, f))) {
          e.f += cf; adj[e.v][e.r].f -= cf; return cf; } } } return 0; }
  int flow(int s, int t) {
    static const int inf = 0x3f3f3f3f;
    int res = 0;
    while(bfs(s,t)) while(int cf=dfs(s,t,inf)) res += cf;
    return res;
  }
}

struct Edge {
  int v; ll d;
  bool operator < (const Edge& o) const {
    return d > o.d;
  }
};

const int N = 1e3 + 1;
const int K = 300 + 1;
vector<Edge> adj[N];
ll dist[N];
ll apsp[K][K];

void dijkstra(int s) {
  memset(dist, INF, sizeof dist);
  priority_queue<Edge> bfs;
  bfs.push({s, 0});
  while(!bfs.empty()) {
    auto [u, d] = bfs.top();
    bfs.pop();
    if(dist[u] < INFLL) continue;
    dist[u] = d;
    for(auto [v, c] : adj[u]) {
      if(dist[v] < INFLL) continue;
      bfs.push({v, d+c});
    }
  }
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  int n, m, k;
  cin >> n >> m >> k;
  vector<int> cli(k);
  for(int i=0; i<k; i++) {
    cin >> cli[i];
  }
  for(int i=0; i<m; i++) {
    int a, b, c;
    cin >> a >> b >> c;
    adj[a].push_back({b, c});
  }

  cli.push_back(0);
  for(int i=0; i<=k; i++) {
    dijkstra(cli[i]);
    for(int j=0; j<=k; j++) {
      apsp[i][j] = dist[cli[j]];
    }
  }

  const int S = 2*k;
  const int T = S+1;
  for(int i=0; i<k; i++) {
    Flow::add_edge(S, i);
    Flow::add_edge(i+k, T);
  }
  for(int i=0; i<k; i++) {
    for(int j=0; j<k; j++) {
      if(i == j) continue;
      if(apsp[k][i] == apsp[k][j] + apsp[j][i]) {
        Flow::add_edge(i, j+k);
      }
    }
  }
  cout << k - Flow::flow(S, T) << nl;

  return 0;
}
