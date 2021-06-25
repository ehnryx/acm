#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include "../../../lca/graph/strongly_connected.h"
#include "../../../lca/graph/dinic.h"

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
  vector remap(n, vector<int>(m));
  vector g(n, vector<char>(m));
  int rid = 0;
  for(int i=0; i<n; i++) {
    for(int j=0; j<m; j++) {
      cin >> g[i][j];
      if(g[i][j] == '#') {
        remap[i][j] = rid++;
      } else {
        g[i][j] = 0;
      }
    }
  }
  vector<int> want(m);
  for(int i=0; i<m; i++) {
    cin >> want[i];
  }

  vector<vector<int>> adj(rid);
  vector<int> last(m, -1);
  for(int i=0; i<n; i++) {
    for(int j=0; j<m; j++) {
      if(!g[i][j]) continue;
      if(i>0 && g[i-1][j]) {
        adj[remap[i-1][j]].push_back(remap[i][j]);
        adj[remap[i][j]].push_back(remap[i-1][j]);
      }
      if(j>0 && g[i][j-1]) {
        adj[remap[i][j-1]].push_back(remap[i][j]);
        adj[remap[i][j]].push_back(remap[i][j-1]);
      }
      if(last[j] != -1) {
        adj[last[j]].push_back(remap[i][j]);
      }
      if(j>0 && last[j-1] != -1) {
        adj[last[j-1]].push_back(remap[i][j]);
      }
      if(j+1<m && last[j+1] != -1) {
        adj[last[j+1]].push_back(remap[i][j]);
      }
      last[j] = remap[i][j];
    }
  }

  strongly_connected<true, true> scc(adj);
  vector<bool> need(scc.size());
  for(int i=n-1; i>=0; i--) {
    for(int j=0; j<m; j++) {
      if(!g[i][j]) continue;
      if(want[j] > 0) {
        want[j]--;
        need[scc[remap[i][j]]] = true;
      }
    }
  }


  return 0;
}
