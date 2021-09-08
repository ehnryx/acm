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
  vector<int> a(n);
  for(int i=0; i<n; i++) {
    cin >> a[i];
  }

  vector<ll> b(n), c(n);
  b[0] = 0;
  c[0] = a[0];
  for(int i=1; i<n; i++) {
    b[i] = b[i-1];
    c[i] = c[i-1];
    if (a[i] > a[i-1]) {
      b[i] += a[i] - a[i-1];
    } else {
      c[i] += a[i] - a[i-1];
    }
  }

  vector<ll> bsum(n), csum(n);
  partial_sum(begin(b), end(b), begin(bsum));
  partial_sum(begin(c), end(c), begin(csum));

  ll ans = numeric_limits<ll>::max();
  for(int i=0; i<n; i++) {
    { // make b[i] = 0
      ll shift = -b[i]; // shift b by -b[i], c by -shift
      auto cmid = prev(upper_bound(begin(c), end(c), shift, greater<>()));
      int j = cmid - begin(c);
      ll bprefix = abs(bsum[i] + shift * (i + 1));
      ll bsuffix = abs((bsum[n - 1] - bsum[i]) + shift * (n - 1 - i));
      ll cprefix = abs(csum[j] - shift * (j + 1));
      ll csuffix = abs((csum[n - 1] - csum[j]) - shift * (n - 1 - j));
      ans = min(ans, bprefix + bsuffix + cprefix + csuffix);
    }
    { // make c[i] = 0
      ll shift = c[i]; // shift b by c[i], c by -shift
      auto bmid = prev(upper_bound(begin(b), end(b), -shift));
      int j = bmid - begin(b);
      ll bprefix = abs(bsum[j] + shift * (j + 1));
      ll bsuffix = abs((bsum[n - 1] - bsum[j]) + shift * (n - 1 - j));
      ll cprefix = abs(csum[i] - shift * (i + 1));
      ll csuffix = abs((csum[n - 1] - csum[i]) - shift * (n - 1 - i));
      ans = min(ans, bprefix + bsuffix + cprefix + csuffix);
    }
  }
  cout << ans << nl;

  return 0;
}
