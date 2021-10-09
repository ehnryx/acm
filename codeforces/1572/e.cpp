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

ll cross(const pair<int, int>& a, const pair<int, int>& b) {
  return (ll)a.first * b.second - (ll)a.second * b.first;
}

const int N = 200 + 1;
pair<int, int> v[N];
ll csum[2*N];
ll dp[N][N][N];

ll solve(int l, int r, int k) {
  if(dp[l][r][k] != -1) return dp[l][r][k];
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

  int n, k;
  cin >> n >> k;
  for(int i=0; i<n; i++) {
    int a, b;
    cin >> a >> b;
    v[i] = pair(a, b);
  }

  for(int i=n-1, j=0; j<n; i=j++) {
    csum[j] = cross(v[i], v[j]); // = j-1 x j
    csum[j+n] = csum[j];
  }

  memset(dp, -1, sizeof dp);
  cout << solve(0, n-1, k) << nl;

  return 0;
}
