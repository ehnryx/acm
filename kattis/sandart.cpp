#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long double ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef pair<ld,ld> pdd;
typedef complex<ld> pt;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-9;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

namespace Flow {
  const int N = 400+2;
  // data structures and helper functions common to all flow routines
  struct Edge { int v, r; ll f, c, p; };
  vector<Edge> adj[N]; int sz[N]; ll mc;
  void init(int n=N) { mc=0; fill(sz,sz+n,0); fill(adj,adj+n,vector<Edge>()); }
  void add_edge(int a, int b, ll c=1, ll p=0) { mc = max(mc,c);
    adj[a].push_back({b, sz[b]++, 0, c, p});
    adj[b].push_back({a, sz[a]++, 0, 0, -p}); }  // change 0 to c for undirected

  // Dinic O(V^2E) in general, O(sqrt(V)E) on unit caps
  // O(VElog(C)) with scaling (C = max edge cap) but worse constant factor
  // USAGE: 1) add edges 2) flow(S, T, scaling?);
  int L[N], cur[N], Q[N];
  bool bfs(int s, int t, ll lim=1) {
    memset(L, INF, sizeof L); memset(cur, 0, sizeof cur);
    int f,b; Q[f=b=0] = s; L[s] = 0; while(f<=b) { int u = Q[f++];
      for(const Edge& e:adj[u]) if(L[e.v] == INF && e.c-e.f >= lim) {
        Q[++b] = e.v; L[e.v] = L[u]+1; } } return L[t] < INF; }
  ll dfs(int u, int t, ll f) { if (u == t) return f;
    ll df = 0; for (int i = cur[u]; i < sz[u] && df < f; cur[u] = ++i) {
      Edge& e = adj[u][i]; if (e.f < e.c && L[e.v] == L[u]+1) {
        ll cf = dfs(e.v, t, min(e.c-e.f, f-df));
        if(cf>=EPS) { e.f += cf; adj[e.v][e.r].f -= cf; df += cf; } } } return df; }
  ll flow(int s, int t, bool scaling=false) { ll inf=numeric_limits<ll>::max();
    ll res = 0; for(int it=0; it<42 && bfs(s,t,EPS); it++) {
      res += dfs(s,t,inf);
    }
    return res; }
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(3);

  int n,m,w,h;
  cin>>n>>m>>w>>h;

  ld v[m];
  for(int i=0;i<m;i++) {
    cin>>v[i];
  }

  ld len[n];
  ld pre = 0;
  for(int i=0;i<n-1;i++) {
    ld x;
    cin>>x;
    len[i] = x-pre;
    pre = x;
  }
  len[n-1] = w-pre;

  ld done[n];
  ld minv[n][m];
  ld minh = INF;
  ld maxh = 0;
  for(int i=0;i<n;i++) {
    ld cur = 0;
    for(int j=0;j<m;j++) {
      cin>>minv[i][j];
      cur += minv[i][j];
      v[j] -= minv[i][j];
    }
    minh = min(minh, cur/len[i]);
    maxh = max(maxh, cur/len[i]);
    done[i] = cur;
  }

  ld maxv[n][m];
  for(int i=0;i<n;i++) {
    for(int j=0;j<m;j++) {
      cin>>maxv[i][j];
    }
  }

  const int S = n+m;
  const int T = S+1;

  ld left = minh;
  ld right = maxh;
  const ld BS = 1e-5;
  while(right-left>BS) {
    ld mid = (left+right)/2;
    Flow::init();
    ld goal = 0;
    for(int i=0;i<n;i++) {
      Flow::add_edge(S, i, len[i]*max((ld)0, mid-done[i]/len[i]));
      goal += len[i]*max((ld)0, mid-done[i]/len[i]);
    }
    for(int i=0;i<m;i++) {
      Flow::add_edge(i+n, T, v[i]);
    }
    for(int i=0;i<n;i++) {
      for(int j=0;j<m;j++) {
        Flow::add_edge(i, j+n, maxv[i][j]-minv[i][j]);
      }
    }
    if(abs(Flow::flow(S,T) - goal) < 2*EPS) {
      left = mid;
    } else {
      right = mid;
    }
  }
  cout<<maxh-left<<nl;

  return 0;
}
