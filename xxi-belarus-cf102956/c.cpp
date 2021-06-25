#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include "../../lca/number/mod_int.h"

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

  const int L = 20;
  vector<Int> add(L);
  vector<int> len(L);
  add[0] = 1;
  len[0] = 2;
  for(int i=1; i<L; i++) {
    len[i] = 2 * len[i-1];
    add[i] = add[i-1] * Int(2).pow(len[i-1]) + add[i-1];
  }

  vector<Int> sub(1<<L);
  for(int k=1; k<L; k++) {
    int s = 1 << k;
    for(int j=0; j<s/2; j++) {
      sub[s+j] = sub[s/2+j];
      sub[s+j+s/2] = sub[s/2+j] + add[k-1];
    }
  }

  int n;
  cin >> n;
  Int ans = 1;
  for(int i=1; i<=n; i++) {
    ans = ans * 2 - sub[i];
  }
  cout << ans - 1 << nl;

  return 0;
}
