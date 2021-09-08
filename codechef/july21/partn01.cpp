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

  

  return 0;
}

/*
 * P(EE) = E(OE) + P(OE) * E(OE) + P(OO) * E(EE)
 * P(EO) = E(OO) + P(OE) * E(OO) + P(OO) * E(EO)
 * P(OE) = O(OE) + P(EE) * O(OE) + P(EO) * O(EE)
 * P(OO) = O(OO) + P(EE) * O(OO) + P(EO) * O(EO)
 * E(EE) = 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, ...
 *       = z / (1-z^4)
 * E(EO) = 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, ...
 *       = 1 / (1-z^4) - 1  [why is there -1]
 * O(EE) = 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, ...
 *       = z^3 / (1-z^4)
 * O(EO) = 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, ...
 *       = z^2 / (1-z^4)
 * etc.
 * maybe there is a direct way to count this
 */
