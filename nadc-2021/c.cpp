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
const int N = 100 * 100 * 2 + 7;
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
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#if defined(ONLINE_JUDGE) && defined(FILENAME)
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif

  int n, m;
  cin >> n >> m;

  vector<int> dsu(n*m, -1);
  function<int(int)> find = [&](int i) {
    if(dsu[i] == -1) return i;
    return dsu[i] = find(dsu[i]);
  };
  function<void(int,int)> link = [&](int i, int j) {
    if(find(i) != find(j)) {
      dsu[find(i)] = find(j);
    }
  };

  vector g(n, vector<char>(m));
  for(int i=0; i<n; i++) {
    for(int j=0; j<m; j++) {
      cin >> g[i][j];
      if(i > 0 && g[i][j] == g[i-1][j]) {
        link(i*m + j, (i-1)*m + j);
      }
      if(j > 0 && g[i][j] == g[i][j-1]) {
        link(i*m + j, i*m + (j-1));
      }
    }
  }

  set<int> outer;
  for(int i : {0, n-1}) {
    for(int j=0; j<m; j++) {
      outer.insert(find(i*m + j));
    }
  }
  for(int i=0; i<n; i++) {
    for(int j : {0, m-1}) {
      outer.insert(find(i*m + j));
    }
  }

  set<pair<int,int>> edges;
  for(int i=0; i<n; i++) {
    for(int j=0; j<m; j++) {
      int u = find(i*m + j);
      if(outer.count(u)) continue;
      if(int v = find((i-1)*m + j); i > 0 && g[i][j] != g[i-1][j] && !outer.count(v)) {
        if(g[i][j] == '0') edges.insert(pair(u, v));
        else edges.insert(pair(v, u));
      }
      if(int v = find(i*m + (j-1)); j > 0 && g[i][j] != g[i][j-1] && !outer.count(v)) {
        if(g[i][j] == '0') edges.insert(pair(u, v));
        else edges.insert(pair(v, u));
      }
    }
  }

  int source = n * m;
  int sink = source + 1;
  set<int> left, right;
  for(auto [a, b] : edges) {
    Flow::add_edge(a, b);
    left.insert(a);
    right.insert(b);
  }
  for(int i : left) {
    Flow::add_edge(source, i);
  }
  for(int i : right) {
    Flow::add_edge(i, sink);
  }

  cout << (int)size(outer) + Flow::flow(source, sink) << nl;

  return 0;
}
