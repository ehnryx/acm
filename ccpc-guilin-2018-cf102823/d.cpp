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
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());



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
  for(int testnum=1; testnum<=T; testnum++) {
    ll x, y;
    cin >> x >> y;
    int ans = 0;
    for(int i=0; i<60; i++) {
      if((x>>i & 1) == (y>>i & 1)) continue;
      if(y>>i & 1) swap(x, y);
      bool ok = false;
      for(int j=i+2; j<60; j+=2) {
        if(y>>j & 1) {
          y ^= 1LL<<j ^ 1LL<<i;
          ans += (j-i)/2;
          ok = true;
          break;
        }
      }
      if(!ok) {
        ans = -1;
        break;
      }
    }
    cout << "Case " << testnum << ": ";
    if(x == y) {
      cout << ans << nl;
    } else {
      cout << -1 << nl;
    }
  }

  return 0;
}
