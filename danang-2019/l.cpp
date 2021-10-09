#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
#define nl '\n'

const int INF = 0x3f3f3f3f;

namespace Flow {
  const int N = 200 + 7;
  struct Edge { int v, r, f, c; };
  vector<Edge> adj[N]; int sz[N];
  void init(int n=N) {
    fill(sz, sz+n, 0); fill(adj, adj+n, vector<Edge>());
  }
  void add_edge(int a, int b, int c=1) {
    adj[a].push_back({b, sz[b]++, 0, c});
    adj[b].push_back({a, sz[a]++, 0, 0});
  }
  int L[N], cur[N], Q[N];
  bool bfs(int s, int t) {
    memset(L, INF, sizeof L); memset(cur, 0, sizeof cur);
    int f,b; Q[f=b=0] = s; L[s] = 0;
    while(f<=b && L[t]==INF) { int u=Q[f++];
      for(const Edge& e:adj[u]) if(L[e.v] == INF && e.c-e.f > 0) {
        Q[++b] = e.v; L[e.v] = L[u]+1; } } return L[t] < INF; }
  int dfs(int u, int t, int f) { if(u == t || !f) return f;
    for(int i=cur[u]; i<sz[u]; cur[u]=++i) {
      Edge& e = adj[u][i];
      if(e.f < e.c && L[e.v] == L[u]+1) {
        if(int cf = dfs(e.v, t, min(e.c-e.f, f))) {
          e.f += cf; adj[e.v][e.r].f -= cf; return cf; } } } return 0; }
  int flow(int s, int t) {
    int res = 0;
    while(bfs(s,t)) {
      while(int cf = dfs(s,t,INF)) res += cf;
    }
    return res;
  }
};

const int N = 100 + 1;
int g[N][N];
unordered_set<int> row[N], col[N];

int main() {
  ios::sync_with_stdio(0); cin.tie(0);

  int n, m;
  cin >> n >> m;
  for(int i=0; i<n; i++) {
    for(int j=0; j<n; j++) {
      cin >> g[i][j];
      if(g[i][j]) {
        if(row[g[i][j]].count(i) || col[g[i][j]].count(j)) {
          cout << "NO" << nl;
          return 0;
        }
        row[g[i][j]].insert(i);
        col[g[i][j]].insert(j);
      }
    }
  }

  const int S = n+n;
  const int T = S+1;
  for(int k=1; k<=n; k++) {
    if(!row[k].empty()) continue;
    Flow::init();
    for(int i=0; i<n; i++) {
      for(int j=0; j<n; j++) {
        if(g[i][j] == 0) {
          Flow::add_edge(i, j+n);
        }
      }
    }
    for(int i=0; i<n; i++) {
      Flow::add_edge(S, i);
      Flow::add_edge(i+n, T);
    }
    if(Flow::flow(S, T) < n) {
      cout << "NO" << nl;
      return 0;
    }
    for(int i=0; i<n; i++) {
      for(const Flow::Edge& e : Flow::adj[i]) {
        if(e.f > 0) {
          assert(g[i][e.v-n] == 0);
          g[i][e.v-n] = k;
        }
      }
    }
  }

  cout << "YES" << nl;
  for(int i=0; i<n; i++) {
    for(int j=0; j<n; j++) {
      cout << g[i][j] << " ";
    }
    cout << nl;
  }

  return 0;
}
