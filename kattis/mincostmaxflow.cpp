#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef int ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef pair<ld,ld> pdd;
typedef complex<ld> pt;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-13;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

namespace Flow {
	const int N = 250;
  struct Edge { int v, r; ll f, c, p; };
  vector<Edge> adj[N]; int sz[N]; //ll mc;
  //vector<Edge> mcf_edges; // for mcf on large graphs with negative costs
  //void init(int n=N) { mc=0; fill(sz,sz+n,0); fill(adj,adj+n,vector<Edge>()); }
  void add_edge(int a, int b, ll c=1, ll p=0) { //mc = max(mc,c);  // scaling
    adj[a].push_back({b,sz[b]++,0,c,p}); // mcf_edges.push_back({b,a,0,c,p});
    adj[b].push_back({a,sz[a]++,0,0,-p}); }
  // Minimum cost maximum flow, assuming there are no negative cost cycles
  // USAGE: 1) add edges 2) min_cost_flow(S, T, price, V, sparse?);
  // use O(V^2) Dijkstra for dense graphs, and O(E*log(V)) otherwise
  // may be faster to use edge list for pot_init on large graphs
  bool vis[N]; int par[N]; ll pot[N], dist[N];
  void pot_init(int n) { fill(pot, pot+n, 0); }
    // if all edge costs >= 0, we don't need to run the Bellman-Ford here
    //for(int i=1; i<n; i++) for(const Edge& e:mcf_edges)
      //if(e.c) pot[e.v] = min(pot[e.v], pot[e.r] + e.p); }
  ll mcf(int s, int t, ll& price, int n, bool sparse) {
    fill(vis, vis+n, 0); fill(dist, dist+n, INF); dist[s] = 0;
    // only need one of the branches below
    if(sparse) {  // replace priority_queue with queue for SPFA
      queue<int> dk; dk.push(s); while(!dk.empty()) {
        int u = dk.front(); dk.pop(); if(vis[u]) continue;
        for(const Edge& e:adj[u]) {  // BUBL;BUBL;BUBL;BUBL;BUBL;BUBL;BUBL;
          if (e.f < e.c && dist[e.v] > dist[u] + pot[u] - pot[e.v] + e.p) {
            dist[e.v] = dist[u] + pot[u] - pot[e.v] + e.p; par[e.v] = e.r;
            dk.push(e.v); } } }
    } else {  // dense
      for(int u = s; u != -1; ) { vis[u] = true; for(const Edge& e: adj[u]) {
        if (e.f < e.c && dist[e.v] > dist[u] + pot[u] - pot[e.v] + e.p) {
          dist[e.v] = dist[u] + pot[u] - pot[e.v] + e.p; par[e.v] = e.r; } }
      u = -1; ll best = INF;
      for(int i=0; i<n; i++) if(!vis[i] && dist[i]<best) best = dist[u=i]; }
    }  // end branches
    if (dist[t] >= INF) { return 0; } ll df = INF;
    for(int u = t; u != s; ) { const Edge& r = adj[u][par[u]];
      df = min(df, adj[r.v][r.r].c - adj[r.v][r.r].f); u = r.v; }
    for(int u = t; u != s; ) { Edge& r=adj[u][par[u]], &e=adj[r.v][r.r];
      e.f += df; r.f -= df; price += df*e.p; u = r.v; }
    for(int i=0; i<n; i++) { pot[i] = min(INF, dist[i]+pot[i]); } return df; }
  ll min_cost_flow(int s, int t, ll& price, int n=N, bool sparse=false) {
    //pot_init(n);
		ll flow = price = 0;
    while(ll df=mcf(s, t, price, n, sparse)) { flow += df; } return flow; }
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	int n,m,s,t;
	cin>>n>>m>>s>>t;
	for(int i=0;i<m;i++) {
		int a,b,c,d;
		cin>>a>>b>>c>>d;
		Flow::add_edge(a,b,c,d);
	}
	ll cost, flow = Flow::min_cost_flow(s,t,cost,n,true);
	cout<<flow<<" "<<cost<<nl;

	return 0;
}
