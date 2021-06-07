#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include "../../../lca/math/linear_sieve.h"

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

int add(int a, int b) {
  return a + b < MOD ? a + b : a + b - MOD;
}

int modpow(ll n, int e) {
  ll r = 1;
  for(;e;e/=2, n = n*n % MOD) {
    if(e&1) r = r*n % MOD;
  }
  return r;
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
  linear_sieve<multiplicative_functions::divisor_num> div(n+1);

  vector<int> dp(n+1), sum(n+1);
  dp[0] = 1;
  sum[0] = 1;
  for(int i=1; i<=n; i++) {
    dp[i] = add(sum[i-1], div[i] - 1);
    sum[i] = add(dp[i], sum[i-1]);
  }
  cout << dp[n] << nl;

  return 0;
}
