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
  const int N = 2500*4+7;
  const int M = N*4;
  int par[N], first[N], nxt[2*M], ep[2*M], m;
  ll flo[2*M], cap[2*M];
  void init() { m = 0; memset(first,-1,sizeof first); memset(flo,0,sizeof flo); }
  void add_edge(int a, int b, ll c=1, ll p=0) { //a,b - nodes, c, p - cap, price
    nxt[m] = first[ep[m]=a], first[ep[m]] = m, cap[m] = c, ++m;
    nxt[m] = first[ep[m]=b], first[ep[m]] = m, cap[m] = 0, ++m;
  }
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

  int n;
  cin >> n;

  int source = 0;
  int sink = 1;
  
  Dinic::init();
  unordered_map<ll,int> node;
  unordered_map<int,ll> value;
  int id = n+2;

  auto add_res = [&] (int i, ll v) {
    if (!node.count(v)) {
      node[v] = id;
      value[id++] = v;
    }
    Dinic::add_edge(i, node[v]);
  };

  int inx[n+2], iny[n+2];
  for (int i=2; i<n+2; i++) {
    ll a, b;
    cin >> a >> b;
    tie(inx[i],iny[i]) = tie(a,b);
    Dinic::add_edge(source, i);
    add_res(i, a+b);
    add_res(i, a-b);
    add_res(i, a*b);
  }

  for (const pair<ll,int>& it : node) {
    Dinic::add_edge(it.second, sink);
  }

  int flow = 0;
  while (Dinic::bfs(source, sink)) {
    flow += Dinic::dfs(source, sink, INF);
  }

  if (flow < n) {
    cout << "impossible" << nl;
  }
  else {
    for (int i=2; i<n+2; i++) {
      for (int e=Dinic::first[i]; e!=-1; e=Dinic::nxt[e]) {
        if (Dinic::flo[e]>0) {
          ll v = value[Dinic::ep[e^1]];
          if (v==inx[i]+iny[i]) cout << inx[i] << " + " << iny[i] << " = " << v << nl;
          else if (v==inx[i]-iny[i]) cout << inx[i] << " - " << iny[i] << " = " << v << nl;
          else cout << inx[i] << " * " << iny[i] << " = " << v << nl;
        }
      }
    }
  }

  return 0;
}
