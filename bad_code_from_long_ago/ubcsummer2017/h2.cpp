#include <bits/stdc++.h>
using namespace std;

#define nl '\n'
#define ll long long
#define pii pair<int,int>
const int INF = 0x3f3f3f3f;

//#define USE_MAGIC_IO
#ifdef USE_MAGIC_IO
inline char get(void) {
  static char buf[100000], *S = buf, *T = buf;
  if (S == T) {
    T = (S = buf) + fread(buf, 1, 100000, stdin);
    if (S == T) return EOF;
  }
  return *S++;
}
inline void read(int &x) {
  static char c; x = 0; int sgn = 0;
  for (c = get(); c < '0' || c > '9'; c = get()) if (c == '-') sgn = 1;
  for (; c >= '0' && c <= '9'; c = get()) x = x * 10 + c - '0';
  if (sgn) x = -x;
}
#else
#define get() getchar()
#define read(x) scanf("%d",&x)
#endif

namespace FLOW {
const int N = 2500+50+2;
const int M = 2500*50 + 2500 + 50 + 2;
// data structures and helper functions common to all flow routines
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

struct Bear {
  int x, y;
  int r;
  int val;
};

int sqr(int x) { return x*x; }

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);

  FLOW::init();

  int n, m;
  cin >> n >> m;

  int sum = 0;
  // add edges
  pii berry[n];
  for (int i = 0; i < n; i++) {
    cin >> berry[i].first >> berry[i].second;
    FLOW::add_edge(50+i+1, 2551, 1);
  }
  Bear bear[m];
  for (int i = 0; i < m; i++) {
    cin >> bear[i].x >> bear[i].y >> bear[i].r >> bear[i].val;
    sum += bear[i].val;
    FLOW::add_edge(0, i+1, bear[i].val);
    for (int j = 0; j < n; j++)
      if (sqr(berry[j].first-bear[i].x) + sqr(berry[j].second-bear[i].y) <= sqr(bear[i].r))
        FLOW::add_edge(i+1, 50+j+1, 1);
  }
  int ans = -1;
  for (int i = 0; i < m; i++) {
    int flow = 0;
    memset(FLOW::flo, 0, sizeof(FLOW::flo));
    while (FLOW::bfs(0, i+1))
      FLOW::dfs(0, i+1, INF);
    while (FLOW::bfs(0, 2551))
      flow += FLOW::dfs(0, 2551, INF);
    //cerr << "flow: " << flow << nl;
    //cerr << "sum: " << sum << nl;
    //cerr << "bear[i].val: " << bear[i].val << nl;
    if (flow == sum - bear[i].val) {
      ans = max(ans, n-flow);
    }
  }
  cout << ans << nl;

  return 0;
}
