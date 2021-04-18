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

  int T;
  cin >> T;
  int xcur = 0, ycur = 0;
  while(T--) {
    int t, x, y;
    cin >> t;
    if(t == 1) {
      ll id;
      cin >> id;
      ll l = 0;
      ll r = 2 * sqrt(id);
      while(l < r) {
        ll m = (l+r) / 2;
        if(id <= 2*m*(m+1)) {
          r = m;
        } else {
          l = m+1;
        }
      }
      assert(id <= 2*r*(r+1));
      if(r == 0) {
        x = 0;
        y = 0;
      } else {
        ll pre = 2*r*(r+1) - 4*r;
        assert(pre < id);
        if(id - pre <= 2*r - 1) {
          id = id - pre;
          x = (id % 2 ? -id/2 : id/2);
          y = r - id/2;
        } else {
          id = id - (pre + 2*r);
          x = r - id;
          y = max(-id, id - 2*r);
        }
      }
      cout << x - xcur << " " << y - ycur << nl;
    } else {
      cin >> x >> y;
      ll r = abs(x) + abs(y);
      if(r == 0) {
        cout << 0 << nl;
      } else {
        ll pre = 2*r*(r+1) - 4*r;
        if(y > 0) {
          cout << pre + 2*abs(x) + (x <= 0) << nl;
        } else {
          cout << pre + 2*r + r - x << nl;
        }
      }
    }
    xcur = x;
    ycur = y;
  }

  return 0;
}
