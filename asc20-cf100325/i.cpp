//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#define FILENAME "starbugs"

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
  const int N = 500 + 7;
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
  //cout << fixed << setprecision(10);
#if defined(ONLINE_JUDGE) && defined(FILENAME)
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif

  int n, k;
  cin >> n >> k;
  vector<int> x(n), y(n), z(n), v(n);
  vector<int> left, right;
  for(int i=0; i<n; i++) {
    cin >> x[i] >> y[i] >> z[i] >> v[i];
    if((x[i] + y[i] + z[i]) % 2) {
      left.push_back(i);
    } else {
      right.push_back(i);
    }
  }

  const int S = n;
  const int T = n+1;
  const int SS = n+2;
  const int TT = n+3;

  vector<tuple<int,int,int>> edges;
  for(int i : left) {
    for(int j : right) {
      if(abs(x[i]-x[j]) + abs(y[i]-y[j]) + abs(z[i]-z[j]) == 1) {
        edges.emplace_back(i, j, v[i] + v[j]);
      }
    }
  }

  int l = 0;
  int r = INF;
  while(l < r) {
    int m = (l+r+1) / 2;

    Flow::init();
    vector<int> deg(n);
    for(const auto& [i, j, c] : edges) {
      if(c >= m) {
        Flow::add_edge(i, j, 1);
        deg[i]++;
        deg[j]++;
      }
    }

    int cnt = 0;
    int iso = 0;
    int lb = INF;
    for(int i : left) {
      if(deg[i]) {
        Flow::add_edge(S, i, INF);
        Flow::add_edge(SS, i, 1);
        Flow::add_edge(S, TT, 1);
        cnt++;
      } else {
        iso++;
        lb = min(lb, v[i]);
      }
    }
    for(int j : right) {
      if(deg[j]) {
        Flow::add_edge(j, T, INF);
        Flow::add_edge(SS, T, 1);
        Flow::add_edge(j, TT, 1);
        cnt++;
      } else {
        iso++;
        lb = min(lb, v[j]);
      }
    }
    Flow::add_edge(T, S, k - iso);

    if(k >= iso && lb >= m && Flow::flow(SS, TT) == cnt) {
      l = m;
    } else {
      r = m-1;
    }
  }

  if(r == 0) {
    cout << -1 << nl;
  } else {
    Flow::init();
    vector<int> deg(n);
    for(const auto& [i, j, c] : edges) {
      if(c >= r) {
        Flow::add_edge(i, j, 1);
        deg[i]++;
        deg[j]++;
      }
    }

    int cnt = 0;
    int iso = 0;
    vector<tuple<ld,ld,ld>> ans;
    for(int i : left) {
      if(deg[i]) {
        Flow::add_edge(S, i, INF);
        Flow::add_edge(SS, i, 1);
        Flow::add_edge(S, TT, 1);
        cnt++;
      } else {
        iso++;
        ans.emplace_back(x[i], y[i], z[i]);
      }
    }
    for(int j : right) {
      if(deg[j]) {
        Flow::add_edge(j, T, INF);
        Flow::add_edge(SS, T, 1);
        Flow::add_edge(j, TT, 1);
        cnt++;
      } else {
        iso++;
        ans.emplace_back(x[j], y[j], z[j]);
      }
    }
    Flow::add_edge(T, S, k - iso);

    Flow::flow(SS, TT);
    for(int i : left) {
      for(const Flow::Edge& e : Flow::adj[i]) {
        if(e.v < n && e.f > 0) {
          ans.emplace_back((x[i]+x[e.v])/(ld)2, (y[i]+y[e.v])/(ld)2, (z[i]+z[e.v])/(ld)2);
        }
      }
    }

    cout << ans.size() << " " << r << nl;
    for(const auto& [a, b, c] : ans) {
      cout << a << " " << b << " " << c << nl;
    }
  }

  return 0;
}
