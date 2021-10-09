#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

//#define FILENAME sadcactus

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
template <typename T>
using ordered_set = __gnu_pbds::tree<T,
      __gnu_pbds::null_type,
      less<T>,
      __gnu_pbds::rb_tree_tag,
      __gnu_pbds::tree_order_statistics_node_update>;

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int INF = 0x3f3f3f3f;
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

const int N = 1e5 + 1;
vector<int> adj[N];
int parent[N];

int dp[N], up[N];
vector<int> prefix[N], suffix[N];

int solve_down(int u, int p, int mod) {
  parent[u] = p;
  if(p) adj[u].erase(find(begin(adj[u]), end(adj[u]), p));
  dp[u] = 1;
  for(int v : adj[u]) {
    int cur = 1 + solve_down(v, u, mod);
    dp[u] = (ll)dp[u] * cur % mod;
    prefix[u].push_back(cur);
  }
  suffix[u] = prefix[u];
  int deg = size(adj[u]);
  for(int i=1; i<deg; i++) {
    prefix[u][i] = (ll)prefix[u][i] * prefix[u][i-1] % mod;
    suffix[u][deg-i-1] = (ll)suffix[u][deg-i-1] * suffix[u][deg-i] % mod;
  }
  return dp[u];
}

void solve_up(int u, int i, int mod) {
  if(parent[u]) {
    up[u] = (1 + up[parent[u]]) % mod;
    if(i > 0) {
      up[u] = (ll)up[u] * prefix[parent[u]][i-1] % mod;
    }
    if(i+1 < size(adj[parent[u]])) {
      up[u] = (ll)up[u] * suffix[parent[u]][i+1] % mod;
    }
  }
  for(int j=0; j<size(adj[u]); j++) {
    solve_up(adj[u][j], j, mod);
  }
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

  int n, mod;
  cin >> n >> mod;
  for(int i=1; i<n; i++) {
    int a, b;
    cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }
  solve_down(1, 0, mod);
  solve_up(1, 0, mod);

  for(int i=1; i<=n; i++) {
    int cur = (1 + up[i]) % mod;
    for(int v : adj[i]) {
      cur = (ll)cur * (1 + dp[v]) % mod;
    }
    cout << cur << nl;
  }

  return 0;
}
