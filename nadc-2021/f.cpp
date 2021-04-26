#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

//#define FILENAME sadcactus

#include "../../lca/graph/strongly_connected.h"

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
  vector<vector<int>> adj(n+1);
  for(int i=1; i<=n; i++) {
    int k;
    cin >> k;
    for(int j=0; j<k; j++) {
      int v;
      cin >> v;
      adj[v].push_back(i);
    }
  }

  strongly_connected scc(adj);
  vector<bool> vis;
  function<int(int)> run = [&](int u) {
    if(vis[u]) return 0;
    vis[u] = true;
    int res = size(scc.group[u]);
    for(int v : scc.dag[u]) {
      res += run(v);
    }
    return res;
  };

  for(int i=1; i<=n; i++) {
    vis = vector<bool>(size(scc.dag), false);
    cout << (run(scc[i]) > m) << nl;
  }

  return 0;
}
