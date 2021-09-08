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
  map<pair<int, int>, vector<ll>> all, other;
  for(int i=0; i<n; i++) {
    int a, b, x, y;
    cin >> a >> b >> x >> y;
    int dx = a - x;
    int dy = b - y;
    int g = gcd(dx, dy);
    dx /= g;
    dy /= g;
    if(dx < 0 || (dx == 0 && dy < 0)) {
      dx = -dx;
      dy = -dy;
    }
    if(dy > 0) {
      ll intercept = (ll)x*dy - (ll)dx*y;
      swap(dx, dy);
      dx = -dx;
      if(dx < 0 || (dx == 0 && dy < 0)) {
        dx = -dx;
        dy = -dy;
      }
      other[pair(dy, dx)].push_back(intercept);
    } else {
      all[pair(dy, dx)].push_back((ll)dx*y - (ll)dy*x);
    }
  }

  ll ans = 0;
  for(auto [slope, vec] : all) {
    if(!other.count(slope)) continue;
    map<ll, int> cnt;
    for(int i=0; i<vec.size(); i++) {
      for(int j=0; j<i; j++) {
        cnt[abs(vec[i] - vec[j])] += 1;
      }
    }
    const auto& ov = other[slope];
    for(int i=0; i<ov.size(); i++) {
      for(int j=0; j<i; j++) {
        ll diff = abs(ov[i] - ov[j]);
        if(auto it = cnt.find(diff); it != cnt.end()) {
          ans += it->second;
        }
      }
    }
  }
  cout << ans << nl;

  return 0;
}
