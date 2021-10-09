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
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;
random_device _rd; mt19937 rng(_rd());

constexpr char nl = '\n';
constexpr ll INF = 0x3f3f3f3f;
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1e9+7;
constexpr ld EPS = 1e-9;

template <class T, class U>
ostream& operator << (ostream& os, const pair<T,U>& v) {
  return os << '(' << v.first << ", " << v.second << ')';
}
template <class T>
ostream& operator << (ostream& os, const vector<T>& v) {
  os << "[ "; for (const T& it : v) { os << it << " , "; }
  return os << ']';
}
template <class T>
ostream& operator << (ostream& os, const set<T>& v) {
  os << "{ "; for (const T& it : v) { os << it << " , "; }
  return os << '}';
}
template <class T, class U>
ostream& operator << (ostream& os, const map<T,U>& v) {
  os << "{ "; for (const pair<T,U>& it : v) { os << it << " , "; }
  return os << '}';
}

template <class T, class U>
istream& operator >> (istream& is, pair<T,U>& v) {
  return is >> v.first >> v.second;
}
template <int i, class... Ts>
istream& read_tuple_impl(istream& is, tuple<Ts...>& v) {
  if constexpr (i == 0) return is;
  else return read_tuple_impl<i-1>(is, v) >> get<i-1>(v);
}
template <class... Ts>
istream& operator >> (istream& is, tuple<Ts...>& v) {
  return read_tuple_impl<sizeof...(Ts)>(is, v);
}

template <class T = int>
vector<T> read_array(int n, int s=0) {
  vector<T> a(n + 2*s);
  for(int i=0; i<n; i++) {
    cin >> a[s+i];
  }
  return a;
}

template <class T = int>
vector<vector<T>> read_grid(int n, int m, int s=0, int t=0) {
  vector a(n + 2*s, vector<T>(m + 2*t));
  for(int i=0; i<n; i++) {
    for(int j=0; j<m; j++) {
      cin >> a[s+i][t+j];
    }
  }
  return a;
}

void solve_case();
void initialize();

////////////////////////////////////////////////////////////////////////

int main(int argc, char** argv) {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  initialize();

  int T;
  cin >> T;
  for (int cc = 1; cc <= T; cc++) {
    auto start = chrono::steady_clock::now();
    cout << "Case #" << cc << ": ";
    solve_case();
    if(argc > 1 && argv[1][0] == 't') {
      cerr << "Time: " << (chrono::steady_clock::now() - start) / 1.0s << "s" << nl << nl;
    }
  }

  return 0;
}

////////////////////////////////////////////////////////////////////////

namespace mcmf {
  const int N = 100 + 7;
  struct Edge { int v, r; ll f, c, p; };
  vector<Edge> adj[N]; int sz[N]; ll mc;
  vector<Edge> mcf_edges; // for mcf on large graphs with negative costs
  void init(int n=N) {
    mc=0; fill(sz,sz+n,0); fill(adj,adj+n,vector<Edge>()); }
  void add_edge(int a, int b, ll c=1, ll p=0) { mc = max(mc,c); // scaling
    // mcf_edges.push_back({b,a,0,c,p});
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

void solve_case() {

#define get(I, J) ((I)*m + (J))
  int n, m, f, s;
  cin >> n >> m >> f >> s;
  const int source = n*m;
  const int sink = n*m + 1;
  const int flip_source = n*m + 2;

  vector a(n, vector<char>(m));
  vector b(n, vector<char>(m));
  int ga = 0;
  for(int i=0; i<n; i++) {
    for(int j=0; j<m; j++) {
      cin >> a[i][j];
      ga += (a[i][j] == 'G');
    }
  }
  int gb = 0;
  for(int i=0; i<n; i++) {
    for(int j=0; j<m; j++) {
      cin >> b[i][j];
      gb += (b[i][j] == 'G');
    }
  }
  if(ga < gb) {
    swap(a, b);
    swap(ga, gb);
  }

  mcmf::init();
  for(int i=0; i<n; i++) {
    for(int j=0; j<m; j++) {
      if(i>0) {
        mcmf::add_edge(get(i, j), get(i-1, j), INF, s);
        mcmf::add_edge(get(i-1, j), get(i, j), INF, s);
      }
      if(j>0) {
        mcmf::add_edge(get(i, j), get(i, j-1), INF, s);
        mcmf::add_edge(get(i, j-1), get(i, j), INF, s);
      }
      if(a[i][j] == 'G') {
        mcmf::add_edge(source, get(i, j), 1, 0);
        mcmf::add_edge(get(i, j), flip_source, 1, 0);
      }
      if(b[i][j] == 'G') {
        mcmf::add_edge(get(i, j), sink, 1, 0);
      }
    }
  }
  mcmf::add_edge(flip_source, sink, abs(ga - gb), f);
  mcmf::add_edge(flip_source, sink, INF, 2 * f);

  ll ans;
  ll flow = mcmf::min_cost_flow(source, sink, ans);
  assert(flow == ga);
  cout << ans << nl;

  return;
}

void initialize() {
}

