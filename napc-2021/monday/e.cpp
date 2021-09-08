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

constexpr ld PI = M_PIl;
constexpr int BS = 99;

ld solve(const vector<int>& lengths) {
  int total = accumulate(begin(lengths), end(lengths), 0);
  if(total <= 2 * lengths.back()) return 0; // sad

  ld l = (ld)lengths.back() / 2;
  ld r = 1e4; // = inf
  for(int bs=0; bs<BS; bs++) {
    ld radius = (l + r) / 2;
    ld angle = 0;
    for(int x : lengths) {
      angle += asin((ld)x/2/radius);
    }
    if(angle < PI) {
      r = radius;
    } else {
      l = radius;
    }
  }
  if(r > (ld)lengths.back() / 2 + EPS) { // done
    ld area = 0;
    for(int x : lengths) {
      ld angle = asin((ld)x/2/r);
      area += sin(2*angle) * r * r / 2;
    }
    return area;
  }

  l = (ld)lengths.back() / 2;
  r = 1e4;
  for(int bs=0; bs<BS; bs++) {
    ld radius = (l + r) / 2;
    ld angle = -2 * asin((ld)lengths.back()/2/radius);
    for(int x : lengths) {
      angle += asin((ld)x/2/radius);
    }
    if(angle < 0) {
      l = radius;
    } else {
      r = radius;
    }
  }
  {
    ld big_angle = asin((ld)lengths.back()/2/r);
    ld area = -2 * sin(2*big_angle) * r * r / 2;
    for(int x : lengths) {
      ld angle = asin((ld)x/2/r);
      area += sin(2*angle) * r * r / 2;
    }
    return area;
  }
}

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
  vector<int> lengths(n);
  for(int i=0; i<n; i++) {
    cin >> lengths[i];
  }
  sort(begin(lengths), end(lengths));

  ld ans = 0;
  for(int i=3; i<=n; i++) {
    vector<int> guess(begin(lengths), begin(lengths) + i);
    ans = max(ans, solve(guess));
  }
  if(ans < EPS) cout << 0 << nl;
  else cout << ans << nl;

  return 0;
}
