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

struct Item {
  int w, s, v;
  Item(int _w, int _s, int _v): w(_w), s(_s), v(_v) {}
  bool operator < (const Item& o) const {
    return s + w < o.s + o.w;
  }
};

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
  vector<Item> ev;
  for(int i=0; i<n; i++) {
    int w, s, v;
    cin >> w >> s >> v;
    ev.emplace_back(w, s, v);
  }
  sort(begin(ev), end(ev));

  const int M = 1e4 + 1;
  vector<ll> dp(M+1); // [idx][weight] = value
  for(auto [w, s, v] : ev) {
    for(int j=s; j>=0; j--) {
      int nw = min(M, j + w);
      dp[nw] = max(dp[nw], dp[j] + v);
    }
  }
  cout << *max_element(begin(dp), end(dp)) << nl;

  return 0;
}
