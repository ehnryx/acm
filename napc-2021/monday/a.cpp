#pragma GCC optimize("O3,fast-math")

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

const ld PI = M_PIl;

vector<vector<bool>> build_adj(const vector<pt>& v, int d) {
  ll d2 = (ll)d * d;
  int n = size(v);
  vector adj(n, vector<bool>(n));
  for(int i=0; i<n; i++) {
    const pt& base = v[i];
    ld l = -1789;
    ld r = 1789;
    for(int j=i+1; j<n; j++) {
      ld angle = arg(v[j] - base);
      ld mid = (l + r) / 2;
      while(angle > mid + PI) {
        angle -= 2 * PI;
      }
      while(angle < mid - PI) {
        angle += 2 * PI;
      }
      if(norm(v[j] - base) > d2) {
        // intersect angles
        ld radius = asin(d / abs(v[j] - base)) + EPS; // enlarge slightly
        l = max(l, angle - radius);
        r = min(r, angle + radius);
      }
      adj[i][j] = (l <= angle && angle <= r);
    }
  }
  return adj;
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

  int n, d;
  cin >> n >> d;
  vector<pt> v;
  for(int i=0; i<n; i++) {
    int a, b;
    cin >> a >> b;
    v.emplace_back(a, b);
  }

  auto f_adj = build_adj(v, d);
  reverse(begin(v), end(v));
  auto b_adj = build_adj(v, d);

  vector<int> dp(n, numeric_limits<int>::max());
  dp[0] = 1;
  for(int i=1; i<n; i++) {
    for(int j=0; j<i; j++) {
      if(f_adj[j][i] && b_adj[n-1-i][n-1-j]) {
        dp[i] = min(dp[i], dp[j] + 1);
      }
    }
  }

  cout << dp[n-1] << nl;

  return 0;
}
