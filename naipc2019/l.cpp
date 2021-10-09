#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int N = 2e5+2;
const int M = N+1e5;
namespace Dinic {
  int par[N], first[N], nxt[2*M], ep[2*M], m;
  ll flo[2*M], cap[2*M], cost[2*M];
  void init() { m = 0; memset(first,-1,sizeof first); memset(flo,0,sizeof flo); }
  void add_edge(int a, int b, ll c=1, ll p=0) { //a,b - nodes, c, p - cap, price
    nxt[m] = first[ep[m]=a], first[ep[m]] = m, cap[m] = c, cost[m] =  p, ++m;
    nxt[m] = first[ep[m]=b], first[ep[m]] = m, cap[m] = 0, cost[m] = -p, ++m; }

  // Dinic's fast maximum flow: tested on NAIPC 2015 F but not theoretically
  // proven to be floating-point-safe.
  // USAGE: 1) init(); 2) add edges
  // 3) ll flow=0; while (bfs(S, T)) flow += dfs(S, T, INF);
  // V^2E in general, min(V^(2/3),sqrt(E))E on unit caps, sqrt(V)E on bipartite
  int L[N], cur[N];
  bool bfs(int s, int t) {
    memset(L, INF, sizeof L);
    queue<int> q; q.push(s); L[s] = 0;
    while (!q.empty()) { int u = q.front(); q.pop();
      for (int v, e = cur[u] = first[u]; e != -1; e = nxt[e])
        if (L[v=ep[e^1]] == INF && flo[e] < cap[e])
          q.push(v), L[v] = L[u]+1;
    } return L[t] < INF; }
  ll dfs(int u, int t, ll f) {
    if (u == t) return f;
    ll cf, df = 0;
    for (int v, e = cur[u]; e != -1 && df < f; cur[u] = e = nxt[e])
      if (flo[e] < cap[e] && L[v=ep[e^1]] == L[u]+1) {
        cf = dfs(v, t, min(cap[e]-flo[e], f-df));
        flo[e] += cf; flo[e^1] -= cf; df += cf;
      } return df; }
}

//#define FILEIO
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);
#ifdef FILEIO
  freopen("test.in", "r", stdin);
  freopen("test.out", "w", stdout);
#endif

  Dinic::init();
  const int s = 0;
  const int t = 2e5+1;

  int n, m;
  cin >> n >> m;

  vector<pii> edges;
  for (int i=0; i<m; i++) {
    int a, b;
    cin >> a >> b;
    edges.push_back({a,b});
    Dinic::add_edge(a, b+n);
  }

  for (int i=1; i<=n; i++) {
    Dinic::add_edge(s, i);
    Dinic::add_edge(i+n, t);
  }

  int flow = 0;
  while (Dinic::bfs(s, t)) {
    flow += Dinic::dfs(s, t, INF);
  }
  if (n-flow==1) {
    cout << 0 << nl;
    return 0;
  }

  unordered_set<int> left, right;
  {
    using namespace Dinic;
    for (int i=1; i<=n; i++) {
      if (L[i] < INF) {
        left.insert(i);
        //cerr << "left: " << i << nl;
      }
    }

    init();
    for (const pii& it : edges) {
      add_edge(it.second, it.first+n);
    }
    for (int i=1; i<=n; i++) {
      add_edge(s, i);
      add_edge(i+n, t);
    }
    while (bfs(s, t)) {
      dfs(s, t, INF);
    }
    for (int i=1; i<=n; i++) {
      if (L[i] < INF) {
        right.insert(i);
        //cerr << "right: " << i << nl;
      }
    }
  }

  cout << n-flow-1 << nl;
  for (int i=1; i<=n; i++) {
    if (left.count(i) || right.count(i)) {
      cout << i << " ";
    }
  }
  cout << nl;

  return 0;
}
