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
const ld EPS = 1e-13;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

namespace Flow {
  const int N = 3e5 + 2;
  struct Edge { int v, r; int f, c; };
  vector<Edge> adj[N]; int sz[N];
  void add_edge(int a, int b, int c=1) {
  adj[a].push_back({b,sz[b]++,0,c});
  adj[b].push_back({a,sz[a]++,0,0}); }
  int L[N], cur[N], Q[N];
  bool bfs(int s, int t, int lim=1) {
    memset(L, INF, sizeof L); memset(cur, 0, sizeof cur);
    int f,b; Q[f=b=0] = s; L[s] = 0; while(f<=b && L[t]==INF) { int u = Q[f++];
      for(const Edge& e:adj[u]) if(L[e.v] == INF && e.c-e.f >= lim) {
        Q[++b] = e.v; L[e.v] = L[u]+1; } } return L[t] < INF; }
  int dfs(int u, int t, int f) { if (u == t || !f) return f;
    for (int i = cur[u]; i < sz[u]; cur[u] = ++i) { Edge& e = adj[u][i];
      if(e.f<e.c && L[e.v]==L[u]+1) { if(int cf = dfs(e.v, t, min(e.c-e.f, f))) {
        e.f += cf; adj[e.v][e.r].f -= cf; return cf; } } } return 0; }
  int flow(int s, int t, bool scaling=false) { int inf=numeric_limits<int>::max();
    int res = 0; int lim = 1;
    while(bfs(s,t,lim)) while(int cf=dfs(s,t,inf)) res += cf;
    return res;
  }
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  int n;
  cin >> n;

  unordered_map<string,int> idx;
  int bmidx[1<<10];
  int id = 0;
  for(int i=0; i<n; i++) {
    int m;
    cin >> m;
    vector<string> vs;
    for(int j=0; j<m; j++) {
      string s;
      cin >> s;
      vs.push_back(s);
    }
    sort(vs.begin(), vs.end());

    for(int bm=1; bm<1<<m; bm++) {
      string cur;
      for(int j=0; j<m; j++) {
        if(bm&1<<j) {
          cur += " " + vs[j];
        }
      }
      if(idx.count(cur)) {
        bmidx[bm] = idx[cur];
        continue;
      }

      int u = bmidx[bm] = idx[cur] = id++;
      for(int sm=bm&(bm-1); sm!=0; sm=bm&(sm-1)) {
        int v = bmidx[sm];
        Flow::add_edge(2*v+1, 2*u);
      }
    }
  }

  const int S = 2*id;
  const int T = 2*id+1;
  for(int i=0; i<id; i++) {
    Flow::add_edge(S, 2*i+1);
    Flow::add_edge(2*i, T);
  }
  cout << id - Flow::flow(S,T) << nl;

  return 0;
}
