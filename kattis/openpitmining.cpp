#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include <ext/rope>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_cxx;
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;
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
  const int N = 202;
  struct Edge { int v, r; ll f, c, p; };
  vector<Edge> adj[N]; int sz[N]; ll mc;
  vector<Edge> mcf_edges; // for mcf on large graphs with negative costs
  void init(int n=N) { mc=0; fill(sz,sz+n,0); fill(adj,adj+n,vector<Edge>()); }
  void add_edge(int a, int b, ll c=1, ll p=0) { mc = max(mc,c);  // scaling
    adj[a].push_back({b,sz[b]++,0,c,p}); // mcf_edges.push_back({b,a,0,c,p});
    adj[b].push_back({a,sz[a]++,0,0,-p}); }

  // Dinic O(V^2E) in general, O(sqrt(V)E) on unit caps
  // O(VElog(C)) with scaling (C = max edge cap) but worse constant factor
  // USAGE: 1) add edges 2) flow(S, T, scaling?);
  // not proven to be floating point safe, worked on naipc 2015 F;  try this:
  // flow = 0; for(int it=0; it<K && bfs(s,t,EPS); it++) flow += dfs(s,t,inf);
  int L[N], cur[N], Q[N];
  bool bfs(int s, int t, ll lim=1) {
    memset(L, INF, sizeof L); memset(cur, 0, sizeof cur);
    int f,b; Q[f=b=0] = s; L[s] = 0; while(f<=b) { int u = Q[f++];
      for(const Edge& e:adj[u]) if(L[e.v] == INF && e.c-e.f >= lim) {
        Q[++b] = e.v; L[e.v] = L[u]+1; } } return L[t] < INF; }
  ll dfs(int u, int t, ll f) { if (u == t) return f;
    ll df = 0; for (int i = cur[u]; i < sz[u] && df < f; cur[u] = ++i) {
      Edge& e = adj[u][i]; if (e.f < e.c && L[e.v] == L[u]+1) {
        ll cf = dfs(e.v, t, min(e.c-e.f, f-df));
        if(cf) { e.f += cf; adj[e.v][e.r].f -= cf; df += cf; } } } return df; }
  ll flow(int s, int t, bool scaling=false) { ll inf=numeric_limits<ll>::max();
    ll res = 0; for(ll lim=(scaling?mc:1); lim; lim/=2) {
      while(bfs(s,t,lim)) res += dfs(s,t,inf); } return res; }
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  int n;
  cin>>n;
  const int s = 0;
  const int t = n+1;
  int v[n],c[n];
  for(int i=1;i<=n;i++) {
    cin>>v[i]>>c[i];
    if(v[i]-c[i] > 0) Flow::add_edge(s,i,v[i]-c[i]);
    else Flow::add_edge(i,t,c[i]-v[i]);
    int m;
    cin>>m;
    for(int j=0;j<m;j++) {
      int k;
      cin>>k;
      Flow::add_edge(k,i,INF);
    }
  }
  Flow::flow(s,t);

  int ans = 0;
  for(int i=1;i<=n;i++) {
    if(Flow::L[i]<INF) {
      //cerr<<i<<" is in closure"<<nl;
      ans += v[i]-c[i];
    }
  }
  cout<<ans<<nl;

  return 0;
}
