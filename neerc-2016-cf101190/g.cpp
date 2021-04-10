//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#define FILENAME sadcactus

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

namespace SCC {
  const int N = 1e5 + 1;
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

// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);
#if defined(ONLINE_JUDGE) && defined(FILENAME)
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif

  int n, m;
  cin >> n >> m;
  for(int i=0; i<m; i++) {
    int a, b;
    cin >> a >> b;
    SCC::adj[a].push_back(b);
  }
  SCC::get_scc(n);

  vector<vector<int>> verts(n + 1);
  vector<bool> inf(n + 1);
  vector<int> outdeg(n + 1);
  for(int i=1; i<=n; i++) {
    verts[SCC::scomp[i]].push_back(i);
    for(int j : SCC::adj[i]) {
      if(SCC::scomp[j] == SCC::scomp[i]) {
        inf[SCC::scomp[i]] = true;
      } else {
        outdeg[SCC::scomp[i]]++;
      }
    }
  }

  int nn = SCC::scompNum;
  for(int i=0; i<nn; i++) {
    cout << i << " -> " << inf[i] << " outdeg " << outdeg[i] << nl;
  }
  assert(verts[nn].empty());

  return 0;
}
