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

namespace Flow {
  const int N = 300 * 300 + 2;
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

  const int S = 0;
  const int T = k*n + 1;
  for(int i=0; i<k; i++) {
    Flow::add_edge(S, i*n + i + 1);
    Flow::add_edge(i*n + n, T, k);
  }

  for(int i=0; i<m; i++) {
    int a, b;
    cin >> a >> b;
    for(int j=0; j<k; j++) {
      Flow::add_edge(j*n + a, ((j+1)%k)*n + b);
    }
  }

  int flow = Flow::flow(S, T);
  cout << flow << nl;

  return 0;
}
