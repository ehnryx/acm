#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

//#define DEBUG

#define ll long long
#define pii pair<int,int>
#define pdd pair<ldouble,ldouble>
#define ldouble long double
#define pt complex<ldouble>
#define ld ldouble
#define nl '\n'
const ll MOD = 1e9+7;
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ldouble EPS = 1e-9;

namespace FLOW {
  const int N = 12*12*12 + 2;
  const int M = 8*N;
  int par[N], first[N], nxt[2*M], ep[2*M], m;
  ll flo[2*M], cap[2*M], cost[2*M];
  void init() { m = 0; memset(first, -1, sizeof first); memset(flo, 0, sizeof flo); }
  void add_edge(int a, int b, ll c=1, ll p=0) {
    nxt[m] = first[ep[m]=a], first[ep[m]] = m, cap[m] = c, cost[m] = p, ++m;
    nxt[m] = first[ep[m]=b], first[ep[m]] = m, cap[m] = 0, cost[m] = -p, ++m; }

  int L[N], cur[N];
  bool bfs(int s, int t) {
    memset(L, INF, sizeof L);
    queue<int> q; q.push(s); L[s] = 0;
    while (!q.empty()) {
      int u = q.front(); q.pop();
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
      }
    return df;
  }
}

#define get(A,B,C) (A)*12*12 + (B)*12 + (C)

int main() {
  ios::sync_with_stdio(0); 
  cin.tie(0); cout.tie(0);

  const int source = 12*12*12;
  const int sink = source+1;

  int n;
  int x, y, z;

  int T;
  cin >> T;
  while (T--) {
    FLOW::init();
    for (int i = 0; i <= 11; i++) {
      for (int j = 0; j <= 11; j++) {
        for (int k = 0; k <= 11; k++) {
          if (i > 0) FLOW::add_edge(get(i,j,k), get(i-1,j,k));
          if (j > 0) FLOW::add_edge(get(i,j,k), get(i,j-1,k));
          if (k > 0) FLOW::add_edge(get(i,j,k), get(i,j,k-1));
          if (i < 11) FLOW::add_edge(get(i,j,k), get(i+1,j,k));
          if (j < 11) FLOW::add_edge(get(i,j,k), get(i,j+1,k));
          if (k < 11) FLOW::add_edge(get(i,j,k), get(i,j,k+1));
          if (i == 0 || j == 0 || k == 0 || i == 11 || j == 11 || k == 11)
            FLOW::add_edge(get(i,j,k), sink);
        }
      }
    }
    cin >> n;
    for (int i = 0; i < n; i++) {
      cin >> x >> y >> z;
      FLOW::add_edge(source, get(x+1, y+1, z+1), INF);
    }
    int flow = 0;
    while (FLOW::bfs(source, sink))
      flow += FLOW::dfs(source, sink, INF);
    cout << flow << nl;
  }

  return 0;
}
