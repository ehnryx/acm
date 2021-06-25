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

typedef long long ll;
typedef long double ld;
typedef complex<ld> pt;

constexpr char nl = '\n';
constexpr ll INF = 0x3f3f3f3f;
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 1e9 + 7;
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

  const int N = 2e5 + 7;
  vector<Int> fact(N), invf(N);
  fact[0] = invf[0] = 1;
  for(int i=1; i<N; i++) {
    fact[i] = fact[i-1] * i;
    invf[i] = fact[i].inverse();
  }
  function<Int(int,int)> choose = [=](int n, int r) {
    if(r<0 || n<r) return Int(0);
    return fact[n] * invf[r] * invf[n-r];
  };

  int T;
  cin >> T;
  while(T--) {
    int n, k;
    cin >> n >> k;
    Int ans = 0;
    for(int r=1; r<=n; r++) {
      int m = n - r - (r-1) * (k-1);
      if(m < 0) break;
      ans += choose(m+r, r) * fact[r] * fact[n-r];
    }
    cout << ans * invf[n] + 1 << nl;
  }

  return 0;
}
