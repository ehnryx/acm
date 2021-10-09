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
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef pair<ld,ld> pdd;
typedef complex<ld> pt;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-9;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

namespace Flow {
  const int N = 50+1;
  struct Edge { int v, r, f, c; };
  vector<Edge> adj[N]; int sz[N];
  void init(int n=N) {
    fill(sz,sz+n,0); fill(adj,adj+n,vector<Edge>()); }
  void add_edge(int a, int b, int c=1) {
    adj[a].push_back({b,sz[b]++,0,c});
    adj[b].push_back({a,sz[a]++,0,0}); }
  int L[N], cur[N], Q[N];
  bool bfs(int s, int t) {
    memset(L, INF, sizeof L); memset(cur, 0, sizeof cur);
    int f,b; Q[f=b=0] = s; L[s] = 0;
    while(f<=b && L[t]==INF) { int u = Q[f++];
      for(const Edge& e:adj[u]) if(L[e.v] == INF && e.f < e.c) {
        Q[++b] = e.v; L[e.v] = L[u]+1; } } return L[t] < INF; }
  int dfs(int u, int t, int f) { if (u == t || !f) return f;
    for (int i = cur[u]; i < sz[u]; cur[u] = ++i) { Edge& e = adj[u][i];
      if(e.f<e.c && L[e.v]==L[u]+1) {
        if(int cf = dfs(e.v, t, min(e.c-e.f, f))) {
          e.f += cf; adj[e.v][e.r].f -= cf; return cf; } } } return 0; }
  int flow(int s, int t) {
    int res = 0;
    while(bfs(s,t))while(int cf=dfs(s,t,INF))res += cf;
    return res;
  }

  /*
  bool vis[N];
  vector<pair<int,int>> get_cut(int s, int n) {
    memset(vis, 0, sizeof vis);
    stack<int> dfs;
    dfs.push(s);
    vis[s] = true;
    while(!dfs.empty()) {
      int u = dfs.top();
      dfs.pop();
      for(const Edge& e : adj[u]) {
        if(!vis[e.v] && e.f < e.c) {
          dfs.push(e.v);
          vis[e.v] = true;
        }
      }
    }
    vector<pair<int,int>> out;
    for(int u=1; u<=n; u++) {
      if(!vis[u]) continue;
      for(const Edge& e : adj[u]) {
        if(!vis[e.v] && e.c > 0 && e.f == e.c) {
          out.push_back(make_pair(u, e.v));
        }
      }
    }
    return out;
  }
  */

  vector<pair<int,int>> get_cut(int s, int n) {
    vector<pair<int,int>> out;
    for(int u=1; u<=n; u++) {
      if(L[u] == INF) continue;
      for(const Edge& e : adj[u]) {
        if(L[e.v] == INF && e.c > 0) {
          assert(e.f == e.c);
          out.push_back(make_pair(u, e.v));
        }
      }
    }
    return out;
  }
}

const int N = 50+1;
ld cost[N][N], dist[N][N];

struct Event {
  ld cur, dist; int cut;
  Event(ld c, ld d, int t): cur(c), dist(d), cut(t) {}
  bool operator < (int x) { return cur < x; }
};
bool operator < (int x, const Event& v) { return x < v.cur; }

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  int n, m;
  cin >> n >> m;
  fill(&cost[0][0], &cost[0][0]+N*N, 1e12);
  for(int i=1; i<=n; i++) {
    cost[i][i] = 0;
  }
  for(int i=0; i<m; i++) {
    int a, b, c;
    cin >> a >> b >> c;
    cost[a][b] = c;
    Flow::add_edge(a, b);
    ////cerr<<"add edge "<<a<<" "<<b<<nl;
  }

  int mincut = Flow::flow(1, n);
  assert(mincut > 0);
  ////cerr<<"start with mincut "<<mincut<<nl;

  for(int i=1; i<=n; i++) {
    for(int j=1; j<=n; j++) {
      dist[i][j] = cost[i][j];
    }
  }
  for(int k=1; k<=n; k++) {
    for(int i=1; i<=n; i++) {
      for(int j=1; j<=n; j++) {
        dist[i][j] = min(dist[i][j], dist[i][k]+dist[k][j]);
      }
    }
  }

  vector<Event> thresh;
  ld mind = dist[1][n];
  ld cur = 0;

  ////cerr<<"start with dist "<<dist[1][n]<<nl;

  while(cur < 1e5+7) {
    for(int i=1; i<=n; i++) {
      for(int j=1; j<=n; j++) {
        dist[i][j] = cost[i][j];
      }
    }
    for(int k=1; k<=n; k++) {
      for(int i=1; i<=n; i++) {
        for(int j=1; j<=n; j++) {
          dist[i][j] = min(dist[i][j], dist[i][k]+dist[k][j]);
        }
      }
    }
    assert(abs(dist[1][n]-mind) < EPS);

    Flow::init();
    for(int i=1; i<=n; i++) {
      for(int j=1; j<=n; j++) {
        if(i != j && dist[1][i] + cost[i][j] + dist[j][n] < dist[1][n]+EPS) {
          Flow::add_edge(i, j);
        }
      }
    }
    int cut = Flow::flow(1, n);
    //cerr<<"get cut "<<cut<<" -> push "<<cur<<" "<<mind<<" "<<cut<<nl;
    thresh.push_back(Event(cur, mind, cut));
    if (cut == mincut) break;

    vector<pair<int,int>> ce = Flow::get_cut(1, n);
    assert(ce.size() == cut);
    for(int i=1; i<=n; i++) {
      for(int j=1; j<=n; j++) {
        dist[i][j] = cost[i][j];
      }
    }
    for(auto [a,b] : ce) {
      dist[a][b] = 1e12;
    }
    for(int k=1; k<=n; k++) {
      for(int i=1; i<=n; i++) {
        for(int j=1; j<=n; j++) {
          dist[i][j] = min(dist[i][j], dist[i][k]+dist[k][j]);
        }
      }
    }

    ld nxtd = dist[1][n];
    assert(nxtd < 1e9);
    for(auto [a,b] : ce) {
      assert(cost[a][b] < 1e9);
      cost[a][b] += nxtd - mind;
      //cerr<<"upd cost of "<<a<<" "<<b<<" to "<<cost[a][b]<<nl;
    }

    cur += cut * (nxtd - mind);
    mind = nxtd;
  }

  int q;
  cin >> q;
  while(q--) {
    int x;
    cin >> x;
    auto it = upper_bound(thresh.begin(), thresh.end(), x);
    assert(it != thresh.begin());
    auto [lb, dst, cut] = *prev(it);
    //cerr<<"query "<<x<<" get -> "<<lb<<" "<<dst<<" "<<cut<<nl;
    cout << dst + (x-lb)/cut << nl;
  }

  return 0;
}
