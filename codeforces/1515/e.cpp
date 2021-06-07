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
random_device _rd; mt19937 rng(_rd());

ll modpow(ll n, ll e, ll m) {
  ll r = 1;
  for(;e;e/=2, n = n*n % m) {
    if(e&1) r = r*n % m;
  } return r;
}

const int N = 400 + 7;
ll ncr[N][N];
ll interleave(int a, int b) {
  return ncr[a+b][a];
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

  int n, m;
  cin >> n >> m;

  for(int i=0; i<N; i++) {
    ncr[i][0] = ncr[i][i] = 1;
    for(int j=1; j<i; j++) {
      ncr[i][j] = (ncr[i-1][j] + ncr[i-1][j-1]) % m;
    }
  }

  vector<int> p2(n+1);
  for(int i=0; i<=n; i++) {
    p2[i] = modpow(2, i, m);
  }

  // [i][j]: up to i, with j manual
  vector dp(n+2, vector<int>(n+1));
  dp[0][0] = 1;
  for(int i=1; i<=n; i++) {
    for(int j=1; j<=i; j++) {
      // current block of k
      for(int k=1; k<=j; k++) {
        dp[i+1][j] = (dp[i+1][j] + interleave(j - k, k) * p2[k-1] % m * dp[i-k][j-k]) % m;
      }
    }
  }
  cout << accumulate(begin(dp[n+1]), end(dp[n+1]), (ll)0) % m << nl;

  return 0;
}
