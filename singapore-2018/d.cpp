//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
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

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 998244353;
const ld EPS = 1e-9;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());



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
  vector<vector<int>> adj(n+1);
  for(int i=0; i<m; i++) {
    int a, b;
    cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }

  vector<int> vis(n+1);
  bool odd = false;
  int ans = 0;
  for(int i=1; i<=n; i++) {
    if(vis[i]) continue;
    ans++;
    stack<int> dfs;
    dfs.push(i);
    vis[i] = 3;
    while(!dfs.empty()) {
      int u = dfs.top();
      dfs.pop();
      for(int v : adj[u]) {
        if(vis[v]) {
          odd |= (vis[v] == vis[u]);
        } else {
          vis[v] = vis[u] ^ 1;
          dfs.push(v);
        }
      }
    }
  }
  cout << ans - 1 + !odd << nl;

  return 0;
}
