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

const int N = 2e5 + 1;
namespace Tarjan {
  int low[N],vis[N],scomp[N],scompNum,I;
  vector<int> adj[N]; stack<int> verts;
  void scc(int u) { low[u] = vis[u] = ++I; verts.push(u);
    for (int v : adj[u]) {
      if (!vis[v]) scc(v);
      if (scomp[v] == -1) low[u] = min(low[u], low[v]); }
    if (vis[u] <= low[u]) { int v;
      do { v=verts.top(); verts.pop(); scomp[v]=scompNum; }while (v != u);
      ++scompNum; }}
  void get_scc(int n) {
    memset(vis,0,sizeof vis); memset(scomp,-1,sizeof scomp);
    scompNum=I=0; for (int i=1; i<=n; ++i) if (!vis[i]) scc(i); }
}

ll depth[N];
bool vis[N];
ll dfs(const vector<vector<pair<int,int>>>& adj, int u) {
  ll res = 0;
  for(auto [v, c] : adj[u]) {
    if(!vis[v]) {
      vis[v] = true;
      depth[v] = depth[u] + c;
      res = gcd(res, dfs(adj, v));
    } else {
      ll cyc = depth[u] + c - depth[v];
      res = gcd(res, cyc);
    }
  }
  return res;
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

  int n, m;
  cin >> n >> m;
  vector<vector<pair<int,int>>> adj(n + 1);
  for(int i=0; i<m; i++) {
    int a, b, c;
    cin >> a >> b >> c;
    Tarjan::adj[a].push_back(b);
    adj[a].emplace_back(b, c);
  }
  Tarjan::get_scc(n);

  vector<vector<int>> group(Tarjan::scompNum);
  vector<int> remap(n + 1);
  for(int i=1; i<=n; i++) {
    int u = Tarjan::scomp[i];
    remap[i] = group[u].size();
    group[u].push_back(i);
  }

  vector<ll> unit(Tarjan::scompNum);
  for(int u=0; u<Tarjan::scompNum; u++) {
    if(size(group[u]) == 1) continue;
    vector<vector<pair<int,int>>> comp(size(group[u]));;
    for(int i : group[u]) {
      for(auto [j, c] : adj[i]) {
        if(Tarjan::scomp[j] != u) continue;
        comp[remap[i]].emplace_back(remap[j], c);
      }
    }
    fill(vis, vis + size(group[u]), false);
    unit[u] = dfs(comp, 0);
  }

  int q;
  cin >> q;
  for(int i=0; i<q; i++) {
    int v, s, t;
    cin >> v >> s >> t;
    ll g = unit[Tarjan::scomp[v]];
    if(g == 0) {
      if(s == 0) {
        cout << "YES" << nl;
      } else {
        cout << "NO" << nl;
      }
    } else {
      if(gcd(s, t) % gcd(g, t) == 0) {
        cout << "YES" << nl;
      } else {
        cout << "NO" << nl;
      }
    }
  }

  return 0;
}
