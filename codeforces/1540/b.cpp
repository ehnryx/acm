#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include "../../../lca/number/mod_int.h"

//#define FILENAME sadcactus

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int INF = 0x3f3f3f3f;
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;
constexpr int MOD = 1e9 + 7;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

using Int = mod_int<MOD>;

const int N = 200 + 1;
vector<int> adj[N];
int sz[N][N];

int dfs(int u, int p) {
  int s = 1;
  for(int v : adj[u]) {
    if(v == p) continue;
    s += dfs(v, u);
  }
  return s;
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

  int n;
  cin >> n;
  for(int i=1; i<n; i++) {
    int a, b;
    cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }

  for(int i=1; i<=n; i++) {
    for(int v : adj[i]) {
      sz[i][v] = dfs(i, v);
    }
  }

  const Int half = Int(2).inverse();
  const Int invn = Int(n).inverse();

  vector dp(n+1, vector<Int>(n+1));
  dp[0][0] = 1;
  for(int i=0; i<=n; i++) {
    for(int j=0; j<=n; j++) {
      if(i>0) {
        dp[i][j] += dp[i-1][j] * half;
      }
      if(j>0) {
        dp[i][j] += dp[i][j-1] * half;
      }
    }
  }

  vector<vector<Int>> sum(n+1);
  for(int i=0; i<=n; i++) {
    partial_sum(begin(dp[i]), end(dp[i]), back_inserter(sum[i]));
  }

  Int ans = 0;
  for(int i=1; i<=n; i++) {
    vector<int> pre(n+1, -1);
    pre[i] = 0;
    queue<int> bfs;
    bfs.push(i);
    while(!empty(bfs)) {
      int u = bfs.front();
      bfs.pop();
      for(int v : adj[u]) {
        if(pre[v] == -1) {
          pre[v] = u;
          bfs.push(v);
        }
      }
    }

    for(int j=i+1; j<=n; j++) {
      vector<int> path;
      for(int u=j; u!=i; u=pre[u]) {
        path.push_back(u);
      }
      path.push_back(i);
      assert(path.size() >= 2);

      ans += invn * sz[path[0]][path[1]];
      for(int k=1; k+1<path.size(); k++) {
        Int prob = invn * (n - sz[path[k-1]][path[k]] - sz[path[k+1]][path[k]]);
        int l = k;
        int r = (int)path.size() - k - 1;
        Int good = sum[l-1][r-1] * half;
        ans += prob * good;
      }
    }
  }

  cout << ans << nl;

  return 0;
}
