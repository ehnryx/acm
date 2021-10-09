#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

namespace Dinic {
const int N = 420;
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
    } return df; 
}
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  int n, k;
  cin >> n >> k;

  const int source = 0;
  const int sink = n+1;
  Dinic::init();

  int a;
  unordered_set<int> src;
  for (int i = 0; i < k; i++) {
    cin >> a;
    src.insert(a);
    Dinic::add_edge(source, a);
  }
  for (int i = 0; i < k; i++) {
    cin >> a;
    Dinic::add_edge(a, sink);
  }

  string adj;
  for (int i = 1; i <= n; i++) {
    cin >> adj;
    for (int j = 1; j <= n; j++) {
      if (adj[j-1] == '1') {
        Dinic::add_edge(i, j, INF);
      }
    }
  }

  ll flow = 0;
  while (Dinic::bfs(source, sink)) {
    flow += Dinic::dfs(source, sink, INF);
  }

  if (flow < k) {
    cout << "NO" << nl;
  }
  else {
    cout << "YES" << nl;

    using namespace Dinic;
    int ans = 0;
    vector<pii> res[n+1];
    vector<int> par[n+1];
    int destination[n+1];
    int deg[n+1]; memset(deg, 0, sizeof deg);
    for (int it : src) {
      int sss = it;
      destination[sss] = sss;
      while (it != sink) {
        int v = sink;
        for (int e = first[it]; e != -1; e = nxt[e]) {
          if (flo[e] > 0) {
            v = ep[e^1];
            flo[e]--;
            break;
          }
        }
        if (v != sink) {
          if (src.count(v)) {
            deg[sss]++;
            par[v].push_back(sss);
          }
          res[sss].push_back(pii(it, v));
          destination[sss] = v;
        }
        it = v;
      }
      ans += res[sss].size();
      //cerr << sss << " --> " << destination[sss] << endl;
    }

    queue<int> next;
    for (int i : src) {
      if (deg[i] == 0) {
        next.push(i);
      }
    }

    cout << ans << nl;
    unordered_set<int> taken = src;
    while (!next.empty()) {
      int cur = next.front();
      next.pop();
      stack<pii> stk;
      for (const pii& it : res[cur]) {
        if (taken.count(it.second)) {
          stk.push(it);
        } else {
          cout << it.first << " " << it.second << nl;
        }
      }
      while (!stk.empty()) {
        pii e = stk.top();
        stk.pop();
        cout << e.first << " " << e.second << nl;
      }

      for (int i : par[cur]) {
        deg[i]--;
        if (deg[i] == 0) next.push(i);
      }
      taken.erase(cur);
      taken.insert(destination[cur]);
    }
  }

  return 0;
}
