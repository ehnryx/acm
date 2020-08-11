//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#define FILENAME "trade"

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
const ll MOD = 998244353;
const ld EPS = 1e-9;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

namespace Flow {
  const int N = 600 + 7;
  struct Edge { int v, r, f, c; };
  vector<Edge> adj[N]; int sz[N];
  void clear_flow(int n=N) {
    for(int i=0; i<n; i++) for(Edge& e : adj[i]) e.f = 0;
  }
  vector<pair<int,int>> memo;
  void add_edge(int a, int b, int c=1, bool rem=false) {
    if(rem) memo.emplace_back(a, sz[a]);
    adj[a].push_back({b, sz[b]++, 0, c});
    adj[b].push_back({a, sz[a]++, 0, 0});
  }
  int L[N], cur[N], Q[N];
  bool bfs(int s, int t) {
    memset(L, INF, sizeof L);
    memset(cur, 0, sizeof cur);
    int f, b; Q[f=b=0] = s; L[s] = 0;
    while (f<=b && L[t] == INF) {
      int u = Q[f++];
      for(const Edge& e:adj[u]) if(L[e.v] == INF && e.f < e.c) {
        Q[++b] = e.v; L[e.v] = L[u] + 1;
      }
    }
    return L[t] < INF;
  }
  int dfs(int u, int t, int f) {
    if(u == t || !f) return f;
    for(int i=cur[u]; i<sz[u]; cur[u]=++i) {
      Edge& e = adj[u][i];
      if(e.f < e.c && L[e.v] == L[u] + 1) {
        if(int cf = dfs(e.v, t, min(e.c-e.f, f))) {
          e.f += cf; adj[e.v][e.r].f -= cf; return cf;
        }
      }
    }
    return 0;
  }
  int flow(int s, int t) {
    int res = 0;
    while(bfs(s, t)) while(int cf=dfs(s, t, INF)) res += cf;
    return res;
  }
}

// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);
#ifdef ONLINE_JUDGE
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif

  int n, m, k;
  cin >> n >> m >> k;

  const int S = 0;
  const int T = n+m + 1;
  const int SS = n+m + 2;
  const int TT = SS + 1;
  for(int i=0; i<k; i++) {
    int a, b;
    cin >> a >> b;
    Flow::add_edge(a, b+n, 1, true);
  }

  for(int i=1; i<=n; i++) {
    Flow::add_edge(S, i, INF);
    Flow::add_edge(S, TT, 2);
    Flow::add_edge(SS, i, 2);
  }
  for(int i=1; i<=m; i++) {
    Flow::add_edge(i+n, T, INF);
    Flow::add_edge(SS, T, 2);
    Flow::add_edge(i+n, TT, 2);
  }
  Flow::add_edge(T, S, INF);

  int l = 0;
  int r = k;
  while(l < r) {
    int v = (l+r) / 2;
    Flow::clear_flow();
    Flow::adj[T].back().c = v;
    if(Flow::flow(SS, TT) == 2*(n+m)) {
      r = v;
    } else {
      l = v+1;
    }
  }

  Flow::clear_flow();
  Flow::adj[T].back().c = r;
  if(Flow::flow(SS, TT) < 2*(n+m)) {
    cout << -1 << nl;
  } else {
    cout << r << nl;
    for(int i=0; i<k; i++) {
      auto [u, j] = Flow::memo[i];
      if(Flow::adj[u][j].f) {
        cout << i+1 << " ";
      }
    }
    cout << nl;
  }

	return 0;
}
