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

  int k, w, h;
  cin >> k >> w >> h;
  ld l = 0;
  ld r = M_PIl/2;
  for(int bs=0; bs<500; bs++) {
    ld m = (l + r) / 2;
    ld a = m;
    ld y = ((ld)w/2) * tanl(a);
    a = atanl(2 * tanl(a));
    for(int i=1; i<k; i++) {
      y += w * tanl(a);
      a = atanl(2 * tanl(a));
    }
    y += ((ld)w/2) * tanl(a);
    if(y < h) {
      l = m;
    } else {
      r = m;
    }
  }
  cout << 180 * r / M_PIl << nl;

  return 0;
}
