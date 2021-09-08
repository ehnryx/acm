#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include "../../../lca/number/mod_int.h"

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
constexpr int MOD = 1e9 + 7;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

using Int = mod_int<MOD>;

const int N = 3e6 + 2;
Int fact[N], invf[N];
Int ncr(int n, int r) {
  if(r<0 || n<r) return 0;
  return fact[n] * invf[r] * invf[n-r];
}

Int dp[N]; // top mod 3

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

  fact[0] = 1;
  for(int i=1; i<N; i++) {
    fact[i] = fact[i-1] * i;
  }
  invf[N-1] = fact[N-1].inverse();
  for(int i=N-1; i>0; i--) {
    invf[i-1] = invf[i] * i;
  }
  assert(invf[0] == 1);

  int n, q;
  cin >> n >> q;
  int m = 3 * n;
  Int inv3 = Int(3).inverse();

  dp[0] = n + 1; // sum 3k choose 0
  for(int i=1; i<=3*n; i++) {
    Int val = ncr(m+1, i+1) + ncr(m, i) * 2;
    val -= (dp[i-1] - ncr(m, i-1)) * 3;
    if(i-2 >= 0) val -= dp[i-2] - ncr(m, i-2);
    //cerr << "got " << val << nl;
    dp[i] = val * inv3;
  }

  while(q--) {
    int x;
    cin >> x;
    cout << dp[x] << nl;
  }

  return 0;
}
