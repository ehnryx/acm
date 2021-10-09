#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const char nl = '\n';

const int INF = 0x3f3f3f3f;

namespace Flow {
  const int N = 50*50 + 2;
  struct Edge { int v, r; ll f, c; };
  vector<Edge> adj[N]; int sz[N]; ll mc;
  void init(int n=N) {
    mc = 0;
    fill(sz, sz+n, 0);
    fill(adj, adj+n, vector<Edge>());
  }
  void add_edge(int a, int b, ll c) {
    mc = max(mc, c);
    adj[a].push_back({b, sz[b]++, 0, c});
    adj[b].push_back({a, sz[a]++, 0, 0});
  }
  int L[N], cur[N], Q[N];
  bool bfs(int s, int t, ll lim=1) {
    memset(L, INF, sizeof L); memset(cur, 0, sizeof cur);
    int f,b; Q[f=b=0] = s; L[s] = 0;
    while(f<=b && L[t]==INF) { int u=Q[f++];
      for(const Edge& e : adj[u]) if (L[e.v]==INF && e.c-e.f >= lim) {
        Q[++b] = e.v; L[e.v] = L[u]+1; } } return L[t] < INF;
  }
  ll dfs(int u, int t, ll f) { if(u==t || !f) return f;
    for(int i=cur[u]; i<sz[u]; cur[u]=++i) { Edge& e = adj[u][i];
      if (e.f<e.c && L[e.v]==L[u]+1) {
        if(ll cf = dfs(e.v, t, min(e.c-e.f, f))) {
          e.f += cf; adj[e.v][e.r].f -= cf; return cf; } } } return 0;
  }
  ll flow(int s, int t, bool sc=0) {
    ll inf=numeric_limits<ll>::max();
    ll res = 0;
    for(ll lim=(sc?mc:1); lim; lim/=2) {
      while(bfs(s,t,lim)) while(ll cf=dfs(s,t,inf)) res += cf;
    }
    return res;
  }
}

const int N = 50;
char g[N][N];

int get(int i, int j) {
  return i*N + j;
}

int main() {
  ios_base::sync_with_stdio(0); cin.tie(0);

  const int SS = N*N;
  const int TT = N*N+1;

  int T;
  cin >> T;
  while(T--) {
    int n, m;
    cin >> n >> m;
    swap(n,m);
    int d, f, b;
    cin >> d >> f >> b;
    for(int i=0; i<n; i++) {
      for(int j=0; j<m; j++) {
        cin >> g[i][j];
      }
    }

    ll ans = 0;
    Flow::init();
    for(int i=0; i<n; i++) {
      for(int j=0; j<m; j++) {
        if(i==0 || i==n-1 || j==0 || j==m-1) {
          if(g[i][j] == '.') {
            ans += f;
          }
          Flow::add_edge(SS, get(i,j), INF);
        } else {
          if(g[i][j] == '.') {
            Flow::add_edge(get(i,j), TT, f);
          } else {
            Flow::add_edge(SS, get(i,j), d);
          }
        }
        if(i>0) Flow::add_edge(get(i,j), get(i-1,j), b);
        if(i+1<n) Flow::add_edge(get(i,j), get(i+1,j), b);
        if(j>0) Flow::add_edge(get(i,j), get(i,j-1), b);
        if(j+1<m) Flow::add_edge(get(i,j), get(i,j+1), b);
      }
    }
    ans += Flow::flow(SS, TT, true);
    cout << ans << nl;
  }
}
