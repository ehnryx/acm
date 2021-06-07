#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include "../../../lca/math/number_theoretic_transform.h"
#include "../../../lca/number/mod_int.h"

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

using Int = mod_int<MOD>;

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

  vector<Int> a(k+1), b(k+1);
  vector<Int> f(k+1), invf(k+1);
  f[0] = 1;
  for(int i=0; i<=k; i++) {
    invf[i] = f[i].inverse();
    int s = i % 2 ? -1 : 1;
    a[i] = invf[i] * s;
    b[i] = Int(i).pow(k) * invf[i];
    if(i+1 <= k) {
      f[i+1] = f[i] * (i + 1);
    }
  }
  vector<Int> stirling = convolve<MOD>(a, b);

  Int ans = 0;
  Int prod = 1;
  for(int i=1; i<=k; i++) {
    prod = prod * (n - i + 1);
    ans += stirling[i] * prod * Int(n+1).pow(n-i);
  }
  cout << ans << nl;

  return 0;
}
