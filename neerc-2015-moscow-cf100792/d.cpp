//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
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

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 998244353;
const ld EPS = 1e-9;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());



// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);
#if defined(ONLINE_JUDGE) && defined(FILENAME)
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif

  ld h1, t1, h2, t2;
  cin >> h1 >> t1 >> h2 >> t2;
  if(t1 > t2) {
    swap(t1, t2);
    swap(h1, h2);
  }

  ld l = 0;
  ld r = 1e18;
  for(int bs=0; bs<420; bs++) {
    ld m = (l+r) / 2;
    ld d = t1 - sqrt(2*h1 / m);
    ld h2_calc = m * (t2-d)*(t2-d) / 2;
    if(h2_calc > h2) {
      r = m;
    } else {
      l = m;
    }
  }

  ld ans = t1 - sqrt(2*h1 / r);
  cout << ans << nl;
  assert(ans >= 0);

  return 0;
}
