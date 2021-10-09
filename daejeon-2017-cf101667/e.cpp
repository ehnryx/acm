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

namespace Dinic {
  const int N = 102;
  const int M = 1024;

  int par[N], first[N], nxt[2*M], ep[2*M], m;
  ll flo[2*M], cap[2*M], cost[2*M];
  void init() { m = 0; memset(first,-1,sizeof first); memset(flo,0,sizeof flo); }
  void add_edge(int a, int b, ll c=1, ll p=0) { //a,b - nodes, c, p - cap, price
    nxt[m] = first[ep[m]=a], first[ep[m]] = m, cap[m] = c, cost[m] =  p, ++m;
    nxt[m] = first[ep[m]=b], first[ep[m]] = m, cap[m] = 0, cost[m] = -p, ++m; 
  }

  int L[N], cur[N];
  bool bfs(int s, int t) {
    memset(L, INF, sizeof L);
    queue<int> q; q.push(s); L[s] = 0;
    while (!q.empty()) { int u = q.front(); q.pop();
    for (int v, e = cur[u] = first[u]; e != -1; e = nxt[e])
      if (L[v=ep[e^1]] == INF && flo[e] < cap[e])
      q.push(v), L[v] = L[u]+1;
    } return L[t] < INF; 
  }
  ll dfs(int u, int t, ll f) {
    if (u == t) return f;
    ll cf, df = 0;
    for (int v, e = cur[u]; e != -1 && df < f; cur[u] = e = nxt[e])
    if (flo[e] < cap[e] && L[v=ep[e^1]] == L[u]+1) {
      cf = dfs(v, t, min(cap[e]-flo[e], f-df));
      flo[e] += cf; flo[e^1] -= cf; df += cf;
    } return df;
  }

  int get_flow(int u, int v) {
    memset(flo, 0, sizeof flo);
    int res = 0;
    while (bfs(u,v)) {
      res += dfs(u,v,INF);
    }
    return res;
  }
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  int n, m;
  cin >> n >> m;

  map<int,vector<pii>> edges;
  for (int i = 0; i < m; i++) {
    int a, b, c;
    cin >> a >> b >> c;
    edges[c].push_back(pii(a,b));
  }

  int ans = 0;
  Dinic::init();
  for (const pair<int,vector<pii>>& layer : edges) {
    for (const pii& e : layer.second) {
      ans += Dinic::get_flow(e.first, e.second);
    }
    for (const pii& e : layer.second) {
      Dinic::add_edge(e.first, e.second);
      Dinic::add_edge(e.second, e.first);
    }
  }
  cout << ans << nl;

  return 0;
}
