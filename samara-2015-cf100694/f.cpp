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
  const int N = 1e3 + 50 + 10;
  const int M = N*N;

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
};

struct Team {
  int i, j, k;
  int cnt;
  Team(): i(-1), j(-1), k(-1), cnt(-1) {}
  Team(int i, int j, int k, int cnt):
    i(i), j(j), k(k), cnt(cnt) {}
  bool operator > (const Team& v) const {
    return cnt > v.cnt;
  }
};

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  int n, m;
  cin >> n >> m;

  int prod[n+1];
  for (int i=0; i<n; i++) {
    cin >> prod[i];
  }

  string name[n+1];
  for (int i=0; i<n; i++) {
    cin >> name[i];
  }

  string grid[n];
  for (int i=0; i<n; i++) {
    cin >> grid[i];
  }

  vector<Team> team;
  for (int i=0; i<n; i++) {
    for (int j=0; j<i; j++) {
      for (int k=0; k<j; k++) {
        int cnt = 0;
        for (int r=0; r<m; r++) {
          cnt += grid[i][r] == '1' || grid[j][r] == '1' || grid[k][r] == '1';
        }
        team.push_back(Team(k, j, i, cnt));
      }
    }
  }
  sort(team.begin(), team.end(), greater<Team>());

  const int source = n+m;
  const int sink = source+1;

  int best = -1;
  Team ans;

  for (const Team& t : team) {
    if (clock() > 1.789*CLOCKS_PER_SEC) break;

    Dinic::init();
    for (int i=0; i<m; i++) {
      Dinic::add_edge(n+i, sink);
      if (grid[t.i][i] == '1') Dinic::add_edge(t.i, n+i);
      if (grid[t.j][i] == '1') Dinic::add_edge(t.j, n+i);
      if (grid[t.k][i] == '1') Dinic::add_edge(t.k, n+i);
    }
    Dinic::add_edge(source, t.i, prod[t.i]);
    Dinic::add_edge(source, t.j, prod[t.j]);
    Dinic::add_edge(source, t.k, prod[t.k]);

    int flow = 0;
    while (Dinic::bfs(source, sink)) {
      flow += Dinic::dfs(source, sink, INF);
    }

    if (flow > best) {
      best = flow;
      ans = t;
    }
  }

  assert(ans.cnt != -1);

  cout << best << nl;
  cout << name[ans.i] << " " << name[ans.j] << " " << name[ans.k] << nl;

  return 0;
}
