#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include "../../../lca/data_structure/splay_tree.h"

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

using node = splay_node<int, void>;

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

  splay_tree<node> left, right;
  for(int i=0; i<n+1; i++) {
    left.insert(new node(0));
    right.insert(new node(0));
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
      left.insert(new node(x - sl));
      if(dir == 1) {
        right.insert(new node(*left.rbegin() + sl - sr));
        left.erase(left.rbegin());
        //ans += (*right.begin() + sr) - (*left.rbegin() + sl);
      }
    } else if(rb < x) {
      right.insert(new node(x - sr));
      if(dir == 0) {
        left.insert(new node(*right.begin() + sr - sl));
        right.erase(right.begin());
        ans += (*right.begin() + sr) - (*left.rbegin() + sl);
      }
    } else {
      if(dir == 0) {
        left.insert(new node(x - sl));
      } else {
        right.insert(new node(x - sr));
      }
    }


    int pos = *right.begin() + sr;
    ans += dir == 0 ? max(0, x - pos) : max(0, pos - x);

    last_t = t;
  }
  cout << ans << nl;

  splay_tree<node> sad;
  sad.insert(new node(0));
  sad.insert(new node(1));
  sad.insert(new node(2));
  cerr << *sad.begin() << endl;
  cerr << *next(sad.begin()) << endl;
  cerr << *prev(next(sad.begin())) << endl;
  assert(sad.begin() == sad.begin());
  assert(prev(next(sad.begin())) == sad.begin());
  assert(prev(prev(next(next(sad.begin())))) == sad.begin());

  return 0;
}
