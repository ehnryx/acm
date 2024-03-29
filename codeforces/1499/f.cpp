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
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());



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
  for(int i=1; i<n; i++) {
    int a, b;
    cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }

  vector<vector<ll>> dp(n+1);
  vector<int> sz(n+1);
  function<void(int,int)> solve = [&](int u, int p) {
    sz[u] = 1;
    dp[u].push_back(1);
    for(int v : adj[u]) {
      if(v == p) continue;
      solve(v, u);
      ll sum = accumulate(dp[v].begin(), dp[v].end(), (ll)0) % MOD;
      vector<ll> res(sz[u] + sz[v]);
      for(int i=sz[u]-1; i>=0; i--) {
        for(int j=sz[v]-1; j>=0; j--) {
          if(i+j+1 > m) continue;
          int k = max(i, j+1);
          res[k] = (res[k] + dp[u][i] * dp[v][j]) % MOD;
        }
        if(i <= m) {
          res[i] = (res[i] + dp[u][i] * sum) % MOD;
        }
      }
      dp[u] = move(res);
      sz[u] += sz[v];
    }
  };

  solve(1, 0);
  ll ans = accumulate(dp[1].begin(), dp[1].end(), (ll)0) % MOD;
  cout << ans << nl;

  return 0;
}
