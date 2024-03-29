#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include "../../../lca/string/suffix_array.h"

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

vector<ll> solve(const vector<int>& h) {
  vector<ll> sum(size(h));
  vector<pair<int, int>> heights;
  heights.reserve(size(h));
  heights.emplace_back(0, 0);
  for (size_t i = 1; i < size(h); i++) {
    sum[i] = sum[i - 1] + h[i];
    int to = i;
    while (heights.back().first > h[i]) {
      auto [higher, idx] = heights.back();
      heights.pop_back();
      sum[i] -= (ll)(to - idx) * (higher - h[i]);
      to = idx;
    }
    heights.emplace_back(h[i], to);
  }
  return sum;
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
  string s;
  cin >> s;
  suffix_array sa(s);

  vector<int> height = sa.height;
  vector<ll> prefix = solve(height);
  reverse(begin(height) + 1, end(height));
  vector<ll> suffix = solve(height);
  reverse(begin(suffix), end(suffix));

  for (int i = 0; i < n; i++) {
    cout << prefix[sa.rank[i]] + suffix[sa.rank[i]] + n - i << nl;
  }

  return 0;
}
