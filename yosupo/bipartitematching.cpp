#include <bits/stdc++.h>
using namespace std;

constexpr char nl = '\n';
constexpr int INF = 0x3f3f3f3f;

using ll = long long;
using vi = vector<int>;
#define rep(i,s,e) for(int i=(s); i<(e); i++)
#define sz(a) (int)size(a)

namespace Flow {
  const int N = 2e5 + 2;
  struct Edge { int v, r; ll f, c, p; };
  vector<Edge> adj[N]; int sz[N]; ll mc;
  vector<Edge> mcf_edges; // for mcf on large graphs with negative costs
  void init(int n=N) {
    mc=0; fill(sz,sz+n,0); fill(adj,adj+n,vector<Edge>()); }
  void add_edge(int a, int b, ll c=1, ll p=0) { mc = max(mc,c); // scaling
    // mcf_edges.push_back({b,a,0,c,p});
    adj[a].push_back({b,sz[b]++,0,c,p});
    adj[b].push_back({a,sz[a]++,0,0,-p}); }
  int L[N], cur[N], Q[N];
  bool bfs(int s, int t, ll lim=1) {
    memset(L, INF, sizeof L); memset(cur, 0, sizeof cur);
    int f,b; Q[f=b=0] = s; L[s] = 0;
    while(f<=b && L[t]==INF) { int u = Q[f++];
      for(const Edge& e:adj[u]) if(L[e.v] == INF && e.c-e.f >= lim) {
        Q[++b] = e.v; L[e.v] = L[u]+1; } } return L[t] < INF; }
  ll dfs(int u, int t, ll f) { if (u == t || !f) return f;
    for (int i = cur[u]; i < sz[u]; cur[u] = ++i) { Edge& e = adj[u][i];
      if(e.f<e.c && L[e.v]==L[u]+1) {
        if(ll cf = dfs(e.v, t, min(e.c-e.f, f))) {
          e.f += cf; adj[e.v][e.r].f -= cf; return cf; } } } return 0; }
  ll flow(int s, int t, bool scaling=0) {ll inf=numeric_limits<ll>::max();
    ll res = 0; for(ll lim=(scaling?mc:1); lim; lim/=2) {
      while(bfs(s,t,lim))while(ll cf=dfs(s,t,inf))res += cf;} return res;}
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int L, R, M;
  cin >> L >> R >> M;
  //Dinic dinic(L+R+2);
  for(int i=0; i<M; i++) {
    int a, b;
    cin >> a >> b;
    Flow::add_edge(a, b + L, 1);
  }
  int source = L + R;
  int sink = source + 1;
  for(int i=0; i<L; i++) {
    Flow::add_edge(source, i, 1);
  }
  for(int i=0; i<R; i++) {
    Flow::add_edge(i + L, sink, 1);
  }

  cout << Flow::flow(source, sink) << nl;
  for(int i=0; i<L; i++) {
    for(const auto& e : Flow::adj[i]) {
      if(e.f > 0) {
        cout << i << " " << e.v - L << nl;
      }
    }
  }

  return 0;
}
