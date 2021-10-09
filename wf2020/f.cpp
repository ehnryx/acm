#pragma GCC optimize("O3,fast-math")
#pragma GCC target("sse4,avx2")
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
using ld = double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int INF = 0x3f3f3f3f;
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-11L;
random_device _rd; mt19937 rng(_rd());

constexpr ld PI = acos((ld)-1);

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

  int n, d;
  cin >> n >> d;
  vector<pt> v;
  for(int i=0; i<n; i++) {
    int a, b;
    cin >> a >> b;
    v.emplace_back(a, b);
  }

  int ans = 0;
  for(int s=0; s<n; s++) {
    vector<pair<ld, int>> ev;
    for(int i=0; i<n; i++) {
      if(i == s) continue;
      ld angle = arg(v[i] - v[s]);
      ld dist = abs(v[i] - v[s]);
      ld in = angle;
      ld out = angle + PI;
      ev.emplace_back(in, 1);
      ev.emplace_back(out, -1);
      ev.emplace_back(in + 2*PI, 1);
      ev.emplace_back(out + 2*PI, -1);
      if (dist > d + EPS) {
        ld diff = asin(d / dist);
        out = angle + diff;
        in = angle + PI - diff;
        ev.emplace_back(in, 1);
        ev.emplace_back(out, -1);
        ev.emplace_back(in + 2*PI, 1);
        ev.emplace_back(out + 2*PI, -1);
      }
    }
    sort(begin(ev), end(ev));

    int res = 0;
    int cur = 0;
    for(auto [_, t] : ev) {
      cur += t;
      res = max(res, cur);
    }

    ans = max(ans, res + 1);
  }

  cout << ans << nl;

  return 0;
}
