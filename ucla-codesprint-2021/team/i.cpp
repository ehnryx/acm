#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#ifdef HENRYX
#include "../../../lca/geometry2d/point.h"
#include "../../../lca/geometry2d/general.h"
#else
#include "point.h"
#include "general.h"
#endif

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

using P = point<ld>;

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

  int a, b, c, d;
  cin >> a >> b >> c >> d;
  P A(a, b), B(c, d);
  cin >> a >> b >> c >> d;
  P C(a, b), D(c, d);

  if(parallel(A, B, C, D)) {
    cout << -1 << nl;
    return 0;
  }

  P it = line_inter(A, B, C, D);
  if(dot(it - A, B - A) >= 0 && dot(it - C, D - C) >= 0) {
    cout << (ll)floor(it.x) << " " << (ll)floor(it.y) << nl;
  } else {
    cout << -1 << nl;
  }

  return 0;
}
