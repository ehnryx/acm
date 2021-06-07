#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

//#define FILENAME sadcactus

#ifdef HENRYX
#include "../../lca/geometry2d/point.h"
#else
#include "point.h"
#endif

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

  ld x, y; int r;
  for(int tt=1; cin >> x >> y >> r; tt++) {
    point<ld> c(x, y), z = 0;
    bool sad = false;
    sad |= abs(z) > 2;
    for(int i=0; i<r; i++) {
      z = z*z + c;
      sad |= abs(z) > 2;
    }
    cout << "Case " << tt << ": ";
    if(sad) {
      cout << "OUT" << nl;
    } else {
      cout << "IN" << nl;
    }
  }

  return 0;
}
