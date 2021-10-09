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

  string s;
  cin >> s;
  ll k;
  cin >> k;

  ll dx = 0;
  ll dy = 0;
  vector<pair<ll, ll>> to;
  to.emplace_back(dx, dy);
  for(char c : s) {
    if(c == 'L') {
      dx -= 1;
    } else if(c == 'R') {
      dx += 1;
    } else if(c == 'U') {
      dy -= 1;
    } else if(c == 'D') {
      dy += 1;
    } else {
      assert(false);
    }
    to.emplace_back(dx, dy);
  }

  if(dx == 0 && dy == 0) {
    sort(begin(to), end(to));
    cout << unique(begin(to), end(to)) - begin(to) << nl;
    return 0;
  }

  map<pair<ll, ll>, vector<pair<ll, ll>>> range;
  for(auto [x, y] : to) {
    ll bdx = y*dx - x*dy;
    ll offset = dx ? (x + INF*abs(dx)) % abs(dx) : (y + INF*abs(dy)) % abs(dy);
    pair<ll, ll> key(bdx, offset);
    ll v = dx ? (x - offset) / abs(dx) : (y - offset) / abs(dy);
    range[key].emplace_back(v, v + k - 1);
  }

  ll ans = 0;
  for(auto& [_, line] : range) {
    //cerr << _.first << " " << _.second << nl;
    sort(begin(line), end(line));
    ll rb = -INFLL;
    for(auto [l, r] : line) {
      l = max(rb + 1, l);
      ans += r - l + 1;
      rb = r;
    }
  }
  cout << ans << nl;

  return 0;
}
