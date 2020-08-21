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
  vector<int> val(n);
  for(int i=0; i<n; i++) {
    cin >> val[i];
  }
  vector<vector<int>> adj(n);
  vector<int> out(n);
  for(int i=0; i<m; i++) {
    int a, b;
    cin >> a >> b;
    adj[b].push_back(a);
    out[a]++;
  }

  vector<ld> dp(n);
  queue<int> bfs;
  for(int i=0; i<n; i++) {
    if(out[i] == 0) {
      dp[i] = val[i];
      bfs.push(i);
    }
  }
  while(!bfs.empty()) {
    int u = bfs.front();
    bfs.pop();
    for(int v : adj[u]) {
      dp[v] = max(dp[v], max(val[v] + dp[u]/2, dp[u]));
      if(--out[v] == 0) {
        bfs.push(v);
      }
    }
  }

  cout << dp[0] << nl;

  return 0;
}
