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

ll solve(ll a, ll b, ll c) {
  ll ans = numeric_limits<ll>::max() - 7;
  {
    ll d = b - a;
    ll cc = b + d;
    if (c <= cc) {
      ans = min(ans, cc - c);
    }
  }
  {
    ll d = c - b;
    ll aa = b - d;
    if (a <= aa) {
      ans = min(ans, aa - a);
    }
  }
  if ((a + c) % 2 == 0) {
    ll bb = (a + c) / 2;
    if (b <= bb) {
      ans = min(ans, bb - b);
    }
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

  ll a, b, c;
  cin >> a >> b >> c;
  ll ans = solve(a, b, c);
  ans = min(ans, solve(a + 1, b, c) + 1);
  ans = min(ans, solve(a, b, c + 1) + 1);
  ans = min(ans, solve(a, b + 1, c) + 1);
  ans = min(ans, solve(a + 1, b + 1, c) + 2);
  ans = min(ans, solve(a, b + 1, c + 1) + 2);
  ans = min(ans, solve(a + 1, b, c + 1) + 2);
  ans = min(ans, solve(a + 1, b + 1, c + 1) + 3);
  cout << ans << nl;

  return 0;
}
