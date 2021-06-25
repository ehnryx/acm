#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

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
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

ll modpow(ll n, ll e, ll m) {
  ll r = 1;
  for(;e;e/=2, n = n*n % m) {
    if(e&1) r = r*n % m;
  } return r;
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

  int n, k, mod;
  cin >> n >> k >> mod;
  vector f(n+1, vector<ll>(k+1)), g(n+1, vector<ll>(k+1));
  iota(begin(f[1]), end(f[1]), 0);
  for(int N=2; N<=n; N++) {
    for(int K=1; K<=k; K++) {
      for(int i=1; i<N; i++) {
        for(int v=1; v<=K; v++) {
          g[N][K] += (f[i][v] + mod - f[i][v-1]) * (modpow(K-v+1, n-i, mod) + mod - modpow(K-v, n-i, mod)) % mod;
        }
      }
      g[N][K] %= mod;
      f[N][K] = (modpow(K, N, mod) + mod - g[N][K]) % mod;
    }
  }
  cout << f[n][k] << nl;

  return 0;
}
