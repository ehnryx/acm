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

  int n;
  cin >> n;

  multiset<int> left, right;
  for(int i=0; i<n+1; i++) {
    left.insert(0);
    right.insert(0);
  }
  int sl = 0;
  int sr = 0;

  ll ans = 0;
  int last_t = 0;
  for(int i=0; i<n; i++) {
    int t, dir, x;
    cin >> t >> dir >> x;
    int dt = t - last_t;

    sl -= dt;
    sr += dt;

    int lb = sl + *left.rbegin();
    int rb = sr + *right.begin();
    if(x < lb) {
      left.insert(x - sl);
      if(dir == 1) {
        right.insert(*left.rbegin() + sl - sr);
        left.erase(prev(left.end()));
        //ans += (*right.begin() + sr) - (*left.rbegin() + sl);
      }
    } else if(rb < x) {
      right.insert(x - sr);
      if(dir == 0) {
        left.insert(*right.begin() + sr - sl);
        right.erase(right.begin());
        ans += (*right.begin() + sr) - (*left.rbegin() + sl);
      }
    } else {
      if(dir == 0) {
        left.insert(x - sl);
      } else {
        right.insert(x - sr);
      }
    }

    int pos = *right.begin() + sr;
    ans += dir == 0 ? max(0, x - pos) : max(0, pos - x);

    last_t = t;
  }

  cout << ans << nl;

  return 0;
}
