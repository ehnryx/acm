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

const int N = 2e5 + 1;
int value[N];

template <class F>
void solve(vector<tuple<int, int, int>> v, const F& f) {
  transform(begin(v), end(v), begin(v), f);
  int mz = 0;
  int mxy = 0;
  for(const auto& [x, y, z] : v) {
    mz = max(mz, z);
    mxy = max(mxy, x + y);
  }
  for(int i=0; i<size(v); i++) {
    const auto& [x, y, z] = v[i];
    value[i] = max(value[i], mz - z);
    value[i] = max(value[i], mxy - (x + y));
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
  vector<tuple<int, int, int>> ev;
  for(int i=0; i<n; i++) {
    int a, b, c;
    cin >> a >> b >> c;
    ev.emplace_back(a, b, c);
  }

  solve(ev, [](const auto& a) { return a; });
  solve(ev, [](const auto& a) { return tuple(get<1>(a), get<2>(a), get<0>(a)); });
  solve(ev, [](const auto& a) { return tuple(get<2>(a), get<0>(a), get<1>(a)); });

  pair<int, int> ans(numeric_limits<int>::max(), -1);
  for(int i=0; i<n; i++) {
    ans = min(ans, pair(value[i], i+1));
  }
  cout << ans.first << " " << ans.second << nl;

  return 0;
}
