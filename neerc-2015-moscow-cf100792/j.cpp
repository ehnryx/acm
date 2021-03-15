#pragma GCC optimize("O3")
#pragma GCC target("sse4,avx2,abm,fma,tune=native")
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

namespace Flow {
  const int N = 203 * 101 + 7;
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
  void pot_init(int n) { fill(pot, pot+n, 0); }
    // if all edge costs >= 0, we don't need to run the Bellman-Ford here
    //for(int i=1; i<n; i++) for(const Edge& e:mcf_edges)
      //if(e.c) pot[e.v] = min(pot[e.v], pot[e.r] + e.p); }
  ll mcf(int s, int t, ll& price, int n, bool sparse) {
    fill(vis, vis+n, 0); fill(dist, dist+n, INFLL); dist[s] = 0;
    // only need one of the branches below
    if(sparse) {  // replace priority_queue with queue for SPFA
      priority_queue<pair<ll,int>> dk; dk.push({0,s}); while(!dk.empty()){
        int u = dk.top().second; dk.pop(); if(vis[u]) continue;
        for(const Edge& e:adj[u]) { // BUBL;BUBL;BUBL;BUBL;BUBL;BUBL;BUBL;
          if (e.f < e.c && dist[e.v] > dist[u] + pot[u] - pot[e.v] + e.p){
            dist[e.v] = dist[u] + pot[u] - pot[e.v] + e.p; par[e.v] = e.r;
            dk.push({-dist[e.v], e.v}); } } }
    } else {  // dense
      for(int u = s; u != -1; ) { vis[u] = 1; for(const Edge& e: adj[u]) {
        if (e.f < e.c && dist[e.v] > dist[u] + pot[u] - pot[e.v] + e.p) {
          dist[e.v]=dist[u] + pot[u] - pot[e.v] + e.p; par[e.v] = e.r; } }
      u = -1; ll best = INFLL;
      for(int i=0; i<n; i++) if(!vis[i] && dist[i]<best) best=dist[u=i]; }
    }  // end branches
    if (dist[t] >= INFLL) { return 0; } ll df = INFLL;
    for(int u = t; u != s; ) { const Edge& r = adj[u][par[u]];
      df = min(df, adj[r.v][r.r].c - adj[r.v][r.r].f); u = r.v; }
    for(int u = t; u != s; ) { Edge& r=adj[u][par[u]], &e=adj[r.v][r.r];
      e.f += df; r.f -= df; price += df*e.p; u = r.v; }
    for(int i=0;i<n;i++) { pot[i]=min(INFLL, dist[i]+pot[i]); } return df; }
  ll min_cost_flow(int s, int t, ll& price, int n=N, bool sparse=false) {
    pot_init(n); ll flow = price = 0;
    while(ll df=mcf(s,t,price,n,sparse)) {
      flow += df;
    }
    return flow;
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

  int n, k, m;
  cin >> n >> k >> m;

  vector<int> cost(m+1);
  for(int i=1; i<=m; i++) {
    cin >> cost[i];
  }

  const int L = 2*m + 3;
  const int S = L*(n+1);
  const int T = S + 1;

  const ll F = INF;
  ll offset = 0;
  vector<vector<int>> have(n+1);
  for(int i=1; i<=n; i++) {
    for(int j=0; j<=m; j++) {
      // no cost to keep
      Flow::add_edge((i-1)*L + 2*j + 1, i*L + 2*j, k, 0);
      // no cost to add
      Flow::add_edge((i-1)*L + 2*0 + 1, i*L + 2*j, k, 0);
      // add edge to reroute
      Flow::add_edge((i-1)*L + 2*j + 1, i*L - 1, k, 0);
      // connect io nodes
      Flow::add_edge(i*L + 2*j, i*L + 2*j + 1, k, F);
    }

    int ni;
    cin >> ni;
    have[i].resize(ni);
    for(int j=0; j<ni; j++) {
      cin >> have[i][j];
      // add cost to change
      Flow::add_edge(i*L - 1, i*L + 2*have[i][j], k, cost[have[i][j]]);
      // add lower bound
      Flow::add_edge(i*L + 2*have[i][j], i*L + 2*have[i][j] + 1, 1, 0);
      offset -= F;
    }
    offset += k*F;
  }

  // add edge from source
  Flow::add_edge(S, 0*L + 2*0 + 1, k, 0);
  // add edge to sink
  for(int j=0; j<=m; j++) {
    Flow::add_edge(n*L + 2*j + 1, T, k, 0);
  }

  ll ans;
  ll flow = Flow::min_cost_flow(S, T, ans, T+1, true);
  cout << ans - offset << nl;
  //cerr << "flow: " << flow << endl;
  assert(flow == k);

  vector mat(n+2, vector(m+1, 0));
  for(int path=1; path<=k; path++) {
    for(int u=S; u!=T; ) {
      int v = -1;
      for(auto& e : Flow::adj[u]) {
        if(e.f > 0) {
          v = e.v;
          e.f--;
          break;
        }
      }
      if((v+1) % L) {
        mat[v/L][(v%L)/2] = path;
      }
      u = v;
    }
  }

  for(int i=1; i<=n; i++) {
    for(int j : have[i]) {
      cout << mat[i][j] << " ";
    }
    cout << nl;
  }

  return 0;
}
