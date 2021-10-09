//#pragma GCC optimize("O3")
//#pragma GCC target("avx2,sse4,fma")

#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

//#define FILENAME sadcactus

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;
typedef long double ld;
typedef complex<ld> pt;

constexpr char nl = '\n';
constexpr ll INF = 0x3f3f3f3f;
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

namespace Flow {
const int N = 1e5 + 2;
struct Edge { int v, r, f, c; };
vector<Edge> adj[N]; int sz[N];
void init(int n=N) {
  fill(sz,sz+n,0); fill(adj,adj+n,vector<Edge>()); }
void clear_flow(int n=N) {
  for(int i=0; i<n; i++) for(auto& e : adj[i]) e.f = 0; }
void add_edge(int a, int b, int c=1) {
  adj[a].push_back({b,sz[b]++,0,c});
  adj[b].push_back({a,sz[a]++,0,0}); }
int L[N], cur[N], Q[N];
bool bfs(int s, int t) {
  memset(L, INF, sizeof L); memset(cur, 0, sizeof cur);
  int f,b; Q[f=b=0] = s; L[s] = 0;
  while(f<=b && L[t]==INF) { int u = Q[f++];
    for(const Edge& e:adj[u]) if(L[e.v] == INF && e.c > e.f) {
      Q[++b] = e.v; L[e.v] = L[u]+1; } } return L[t] < INF; }
int dfs(int u, int t, int f) { if (u == t || !f) return f;
  for (int i = cur[u]; i < sz[u]; cur[u] = ++i) { Edge& e = adj[u][i];
    if(e.f<e.c && L[e.v]==L[u]+1) {
      if(int cf = dfs(e.v, t, min(e.c-e.f, f))) {
        e.f += cf; adj[e.v][e.r].f -= cf; return cf; } } } return 0; }
int flow(int s, int t) {
  int inf=numeric_limits<int>::max(), res = 0;
  while(bfs(s,t))while(int cf=dfs(s,t,inf))res += cf;
  return res;
}
}

int digit_sum(int n) {
  int res = 0;
  while(n) {
    res += n % 10;
    n /= 10;
  }
  return res;
}

int rotate(int m, int n, int j, int d) {
  string s = to_string(n);
  s = string(m - size(s), '0') + s;
  s[j] = (s[j] - '0' + d) % 10 + '0';
  return stoi(s);
}

// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#if defined(ONLINE_JUDGE) && defined(FILENAME)
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif

  int T;
  cin >> T;
  while(T--) {
    int L, m, s;
    cin >> L >> m >> s;
    int n = pow(10, L);
    vector<bool> bad(n);
    for(int i=0; i<m; i++) {
      int v;
      cin >> v;
      bad[v] = true;
    }
    bool s_par = digit_sum(s) % 2;

    int source = n;
    int sink = n + 1;
    Flow::init(n + 2);
    bad[s] = true;
    for(int i=0; i<n; i++) {
      if(bad[i]) continue;
      bool left = (digit_sum(i) % 2 == s_par);
      if(left) {
        Flow::add_edge(source, i);
      } else {
        Flow::add_edge(i, sink);
      }
      for(int j=0; j<L; j++) {
        int o = rotate(L, i, j, 1);
        if(bad[o]) continue;
        if(left) Flow::add_edge(i, o);
        else Flow::add_edge(o, i);
      }
    }
    int without_s = Flow::flow(source, sink);

    //Flow::clear_flow(n + 2);
    for(int j=0; j<L; j++) {
      for(int d : {1, 9})  {
        int o = rotate(L, s, j, d);
        if(bad[o]) continue;
        Flow::add_edge(s, o);
      }
    }
    Flow::add_edge(source, s);
    int with_s = Flow::flow(source, sink);
    //assert(with_s >= without_s);

    if(with_s) {
      cout << "Alice" << nl;
    } else {
      cout << "Bob" << nl;
    }
  }

  return 0;
}
