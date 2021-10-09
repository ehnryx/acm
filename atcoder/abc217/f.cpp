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

const int N = 400 + 1;
bool adj[N][N];
int dp[N][N];
int ncr[N][N];

int solve(int l, int r) {
  if(r < l) return 1;
  if(dp[l][r] != -1) return dp[l][r];
  ll res = 0;
  for(int i=l+1; i<=r; i++) {
    if(!adj[l][i]) continue;
    ll cur = (ll)solve(l+1, i-1) * solve(i+1, r) % MOD;
    int all = (r-l+1) / 2;
    int left = (i-l+1) / 2;
    res = (res + cur * ncr[all][left]) % MOD;
  }
  return dp[l][r] = res;
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

  for(int i=0; i<N; i++) {
    ncr[i][0] = ncr[i][i] = 1;
    for(int j=1; j<i; j++) {
      ncr[i][j] = (ncr[i-1][j] + ncr[i-1][j-1]) % MOD;
    }
  }

  int n, m;
  cin >> n >> m;
  for(int i=0; i<m; i++) {
    int a, b;
    cin >> a >> b;
    adj[a][b] = true;
  }

  memset(dp, -1, sizeof dp);
  cout << solve(1, 2*n) << nl;

  return 0;
}
