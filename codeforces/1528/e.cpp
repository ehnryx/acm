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

  int n;
  cin >> n;
  vector<Int> b(n+2), s(n+2);
  Int inv2 = Int(2).inverse();

  b[0] = 1;
  s[0] = 0;
  for(int i=1; i<=n; i++) {
    b[i] = b[i-1] * (b[i-1] + 1) * inv2 + b[i-1] * s[i-1];
    s[i] = s[i-1] * (s[i-1] + 1) * inv2 + 1;
    //b[i] = b[i-1] + b[i-1] * (b[i-1] - 1) / 2 + b[i-1] * s[i-1];
    //s[i] = s[i-1] + s[i-1] * (s[i-1] - 1) / 2 + 1;
    //cerr << "b,s[" << i << "] = " << b[i] << " " << s[i] << nl;
  }

  // single tree
  //Int ans = b[n];
  //ans += b[n] * (b[n] - 1);
  //ans += (s[n] + s[n] * (s[n] - 1) / 2) * b[n];
  //ans += (b[n] + b[n] * (b[n] - 1) / 2) * s[n];
  Int ans = b[n] * b[n];
  ans += b[n] * (b[n] - 1) * (b[n] - 2) / 6;
  ans += (s[n] * (s[n] + 1) * inv2) * b[n];
  ans += (b[n] * (b[n] + 1) * inv2) * s[n];
  ans += ans;

  // double tree
  for(int i=1; i<=n; i++) {
    ans += (b[i+1] - b[i]) * b[n-i];
  }

  cout << ans << nl;

  return 0;
}
