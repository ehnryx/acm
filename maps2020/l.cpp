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
typedef complex<ld> pt;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-9;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

namespace Flow {
  const int N = 1e3 + 2;
  struct Edge { int v, r, f, c; };
  vector<Edge> adj[N]; int sz[N];
  void add_edge(int a, int b, int c=1) {
    adj[a].push_back({b,sz[b]++,0,c});
    adj[b].push_back({a,sz[a]++,0,0});
  }
  int L[N], cur[N], Q[N];
  bool bfs(int s, int t) {
    memset(L, INF, sizeof L); memset(cur, 0, sizeof cur);
    int f,b; Q[f=b=0] = s; L[s] = 0;
    while(f<=b && L[t]==INF) {
      int u = Q[f++];
      for(const Edge& e : adj[u]) if(L[e.v] == INF && e.f < e.c) {
        Q[++b] = e.v; L[e.v] = L[u]+1;
      }
    }
    return L[t] < INF;
  }
  int dfs(int u, int t, int f) {
    if(u == t || !f) return f;
    for(int i=cur[u]; i<sz[u]; cur[u]=++i) {
      Edge& e = adj[u][i];
      if(e.f < e.c && L[e.v] == L[u]+1) {
        if(int cf = dfs(e.v, t, min(e.c-e.f, f))) {
          e.f += cf; adj[e.v][e.r].f -= cf; return cf;
        }
      }
    }
    return 0;
  }
  int flow(int s, int t) {
    int res = 0;
    while(bfs(s,t)) {
      while(int cf=dfs(s,t,INF)) res += cf;
    }
    return res;
  }
}

const int N = 500 + 1;
vector<int> adj[N];
int deg[N];
int con[N][N];

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  int n, m;
  cin >> n >> m;
  for(int i=0; i<m; i++) {
    int a, b;
    cin >> a >> b;
    adj[a].push_back(b);
    deg[b]++;
  }

  queue<int> bfs;
  for(int i=0; i<n; i++) {
    if(deg[i] == 0) {
      bfs.push(i);
    }
  }
  while(!bfs.empty()) {
    int u = bfs.front();
    bfs.pop();
    for(int v : adj[u]) {
      if(--deg[v] == 0) {
        bfs.push(v);
      }
    }
  }

  for(int i=0; i<n; i++) {
    for(int j=0; j<n; j++) {
      con[i][j] = INF;
    }
    for(int j : adj[i]) {
      if(deg[i] == 0 && deg[j] == 0) {
        con[i][j] = 0;
      }
    }
  }

  for(int k=0; k<n; k++) {
    for(int i=0; i<n; i++) {
      for(int j=0; j<n; j++) {
        con[i][j] = min(con[i][j], con[i][k]+con[k][j]);
      }
    }
  }

  const int S = 2*n;
  const int T = 2*n+1;
  int cnt = 0;
  for(int i=0; i<n; i++) {
    if(deg[i]) continue;
    cnt++;
    Flow::add_edge(S, i);
    Flow::add_edge(i+n, T);
    for(int j=0; j<n; j++) {
      if(deg[j] || con[i][j] > 0) continue;
      Flow::add_edge(i, j+n);
    }
  }
  int flow = Flow::flow(S, T);
  cout << cnt - flow << nl;
  assert(0 <= flow && flow <= cnt);

  return 0;
}
