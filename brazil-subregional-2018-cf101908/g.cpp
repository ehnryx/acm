#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
using namespace std;

#define nl '\n'

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
const int INF = 0x3f3f3f3f;
const int N = 3000, K = 1010, M = 23000, S = N-1, T = N-2;

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

int p, r, c;
int d[N], e[N];
struct edge {
  int u, v, t;
  bool operator < (const edge& o) const {
    return t < o.t;
  }
};
int target = 0;
vector<edge> edges;

bool check(int maxt) {
  init();
  for (int i = 0; i < c && edges[i].t <= maxt; i++) {
    add_edge(edges[i].v, K+edges[i].u, INF);
  }
  for (int i = 0; i < p; i++) {
    add_edge(K+i, T, d[i]);
  }
  for (int i = 0; i < r; i++) {
    add_edge(S, i, e[i]);
  }
  ll flow = 0;
  while (bfs(S, T)) flow += dfs(S, T, INF);
  //cerr << flow << endl;
  assert(flow <= target);
  return flow >= target;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);

  cin >> p >> r >> c;
  for (int i = 0; i < p; i++) {
    cin >> d[i];
    target += d[i];
  }
  for (int i = 0; i < r; i++) {
    cin >> e[i];
  }
  edges.resize(c);
  for (int i = 0; i < c; i++) {
    cin >> edges[i].u >> edges[i].v >> edges[i].t;
    edges[i].u--; edges[i].v--;
  }
  sort(edges.begin(), edges.end());
  int l = 0, r = 1e6+1, ans = -1;
  while (l <= r) {
    int mid = (l+r)/2;
    if (check(mid)) {
      ans = mid;
      r = mid-1;
    } else l = mid+1;
  }
  cout << ans << nl;

  return 0;
}
