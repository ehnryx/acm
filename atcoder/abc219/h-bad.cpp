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

ll solve(const vector<pair<int, int>>& a, const vector<pair<int, int>>& b) {
  multiset<int> other;
  ll sum = 0;
  for(auto [x, v] : b) {
    if(v > x) {
      sum += v - x;
      other.insert(v - x);
    }
  }

  ll ans = sum;

  ll add = 0;
  int last = 0;
  for(auto [x, v] : a) {
    add += max(0, v - x);
    while(!empty(other) && *begin(other) <= 2*x) {
      int diff = *begin(other) - last;
      sum -= (ll)diff * size(other);
      other.erase(begin(other));
      last += diff;
    }
    sum -= (ll)(2*x - last) * size(other);
    last = 2*x;
    ans = max(ans, add + sum);
  }

  return ans;
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

  ll base = 0;
  vector<pair<int, int>> left, right;
  for(int i=0; i<n; i++) {
    int x, a;
    cin >> x >> a;
    if(x < 0) {
      left.emplace_back(-x, a);
    } else if(x > 0) {
      right.emplace_back(x, a);
    } else {
      base += a;
    }
  }
  sort(begin(left), end(left));
  sort(begin(right), end(right));

  ll ans = base + max(solve(left, right), solve(right, left));
  cout << ans << nl;

  return 0;
}
