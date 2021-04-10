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

namespace Flow {
  const int N = 225;
  struct Edge { int v, r; ll f, c, p; };
  vector<Edge> adj[N]; int sz[N];
  vector<Edge> mcf_edges; // for mcf on large graphs with negative costs
  void init(int n=N) {
    fill(sz,sz+n,0); fill(adj,adj+n,vector<Edge>()); }
  void add_edge(int a, int b, ll c=1, ll p=0) {
    mcf_edges.push_back({b,a,0,c,p});
    adj[a].push_back({b,sz[b]++,0,c,p});
    adj[b].push_back({a,sz[a]++,0,0,-p}); }
  bool vis[N]; int par[N]; ll pot[N], dist[N];
  void pot_init(int n) { fill(pot, pot+n, 0);
    // if all edge costs >= 0, we don't need to run the Bellman-Ford here
    for(int i=1; i<n; i++) for(const Edge& e:mcf_edges)
      if(e.c) pot[e.v] = min(pot[e.v], pot[e.r] + e.p); }
  ll mcf(int s, int t, ll& price, int n, bool sparse) {
    fill(vis, vis+n, 0); fill(dist, dist+n, INF); dist[s] = 0;
    // only need one of the branches below
    if(sparse) {  // replace priority_queue with queue for SPFA
      /*priority_*/queue<pair<ll,int>> dk; dk.push({0,s}); while(!dk.empty()){
        int u = dk.front().second; dk.pop(); if(vis[u]) continue;
        vis[u] = true; for(const Edge& e:adj[u]) { // BUBL;BUBL;BUBL;BUBL;
          if (e.f < e.c && dist[e.v] > dist[u] + pot[u] - pot[e.v] + e.p){
            dist[e.v] = dist[u] + pot[u] - pot[e.v] + e.p; par[e.v] = e.r;
            dk.push({-dist[e.v], e.v}); } } }
    } else {  // dense
      for(int u = s; u != -1; ) { vis[u] = 1; for(const Edge& e: adj[u]) {
        if (e.f < e.c && dist[e.v] > dist[u] + pot[u] - pot[e.v] + e.p) {
          dist[e.v]=dist[u] + pot[u] - pot[e.v] + e.p; par[e.v] = e.r; } }
      u = -1; ll best = INF;
      for(int i=0; i<n; i++) if(!vis[i] && dist[i]<best) best=dist[u=i]; }
    }  // end branches
    if (dist[t] >= INF) { return 0; } ll df = INF;
    for(int u = t; u != s; ) { const Edge& r = adj[u][par[u]];
      df = min(df, adj[r.v][r.r].c - adj[r.v][r.r].f); u = r.v; }
    for(int u = t; u != s; ) { Edge& r=adj[u][par[u]], &e=adj[r.v][r.r];
      e.f += df; r.f -= df; price += df*e.p; u = r.v; }
    for(int i=0;i<n;i++) { pot[i]=min(INF, dist[i]+pot[i]); } return df; }
  ll min_cost_flow(int s, int t, ll& price, int n=N, bool sparse=false) {
    pot_init(n); ll flow = price = 0;
    while(ll df=mcf(s,t,price,n,sparse)) { flow += df; } return flow; }
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

  for(int n, m; cin >> n >> m && n; ) {
    int S = n + m;
    int T = S + 1;
    Flow::init(T + 1);
    for(int i=0; i<n; i++) {
      int p;
      cin >> p;
      Flow::add_edge(S, i, p, 0);
    }
    for(int i=0; i<m; i++) {
      int y;
      cin >> y;
      Flow::add_edge(i + n, T, 1, 0);
      for(int j=0; j<4; j++) {
        int c;
        cin >> c;
        Flow::add_edge(c, i + n, 1, -(y*4 - j));
      }
    }
    ll cost = 0;
    assert(Flow::min_cost_flow(S, T, cost, T + 1, true) == m);
    cout << -cost << nl;
  }

  return 0;
}
