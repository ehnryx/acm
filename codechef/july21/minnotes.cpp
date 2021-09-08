#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

//#define FILENAME sadcactus

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

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

  int T;
  cin >> T;
  while(T--) {
    int n;
    cin >> n;
    vector<int> a(n+2);
    for(int i=1; i<=n; i++) {
      cin >> a[i];
    }

    if(n == 1) {
      cout << 1 << nl;
      continue;
    }

    vector<int> prefix(n+2), suffix(n+2);
    vector<ll> psum(n+2), ssum(n+2);
    for(int i=1; i<=n; i++) {
      prefix[i] = gcd(a[i], prefix[i-1]);
      psum[i] = a[i] + psum[i-1];
    }
    for(int i=n; i>=1; i--) {
      suffix[i] = gcd(a[i], suffix[i+1]);
      ssum[i] = a[i] + ssum[i+1];
    }

    ll ans = numeric_limits<ll>::max();
    for(int i=1; i<=n; i++) {
      int g = gcd(prefix[i-1], suffix[i+1]);
      ans = min(ans, 1 + (psum[i-1] + ssum[i+1]) / g);
    }
    cout << ans << nl;
  }

  return 0;
}
