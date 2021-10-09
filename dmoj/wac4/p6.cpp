//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
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
const ll MOD = 998244353;
const ld EPS = 1e-9;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

namespace Flow {
  const int N = 1000 + 4;
  struct Edge { int v, r; ll f, c; };
  vector<Edge> adj[N]; int sz[N];
  void clear_flow() {
    for(int i=0; i<N; i++) {
      for(Edge& e : adj[i]) {
        e.f = 0;
      }
    }
  }
  void add_edge(int a, int b, ll c=1) {
    adj[a].push_back({b,sz[b]++,0,c});
    adj[b].push_back({a,sz[a]++,0,0}); }
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
    ll res = 0; for(ll lim=(scaling?1<<29:1); lim; lim/=2) {
      while(bfs(s,t,lim))while(ll cf=dfs(s,t,inf))res += cf;} return res;}
}

// TODO
// double-check correctness
// read limits carefully
int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  int n, m;
  cin >> n >> m;
  const int S = n+m;
  const int T = S+1;
  const int SS = S+2;
  const int TT = S+3;
  int a[n], b[n], c[n][m], d[n][m], e[m], f[m];

  ll sat = 0;
  for(int i=0; i<n; i++) {
    cin >> a[i] >> b[i];
    Flow::add_edge(S, i, b[i] - a[i]);
    Flow::add_edge(SS, i, a[i]);
    Flow::add_edge(S, TT, a[i]);
    sat += a[i];
  }
  for(int i=0; i<n; i++) {
    for(int j=0; j<m; j++) {
      cin >> c[i][j];
    }
  }
  for(int i=0; i<n; i++) {
    for(int j=0; j<m; j++) {
      cin >> d[i][j];
      Flow::add_edge(i, n+j, d[i][j] - c[i][j]);
      Flow::add_edge(SS, n+j, c[i][j]);
      Flow::add_edge(i, TT, c[i][j]);
      sat += c[i][j];
    }
  }
  for(int i=0; i<m; i++) {
    cin >> e[i] >> f[i];
    Flow::add_edge(n+i, T, f[i] - e[i]);
    Flow::add_edge(SS, T, e[i]);
    Flow::add_edge(n+i, TT, e[i]);
    sat += e[i];
  }
  Flow::add_edge(T, S, INFLL);
  Flow::add_edge(SS, S, 0);
  Flow::add_edge(T, TT, 0);

  if(Flow::flow(SS, TT) < sat) {
    cout << -1 << nl;
    return 0;
  }

  int last_edge = (int)Flow::adj[T].size() - 2;
  ll left, right;

  left = 0;
  right = INF * min(n, m);
  while(left < right) {
    ll mid = (left + right) / 2;
    Flow::clear_flow();
    Flow::adj[T][last_edge].c = mid;
    if(Flow::flow(SS, TT) < sat) {
      left = mid + 1;
    } else {
      right = mid;
    }
  }
  cout << right << nl;
  Flow::adj[T][last_edge].c = INFLL;

  left = 0;
  right = INF * min(n, m);
  while(left < right) {
    ll mid = (left + right + 1) / 2;
    Flow::clear_flow();
    Flow::adj[SS].back().c = mid;
    Flow::adj[T].back().c = mid;
    if(Flow::flow(SS, TT) < sat + mid) {
      right = mid - 1;
    } else {
      left = mid;
    }
  }
  cout << right << nl;

  return 0;
}
