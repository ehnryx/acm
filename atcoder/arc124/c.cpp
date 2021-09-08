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

vector<int> divisors(int n) {
  vector<int> res;
  for(int i=1; i*i<=n; i++) {
    if(n % i == 0) {
      res.push_back(i);
      if(i*i < n) res.push_back(n/i);
    }
  }
  return res;
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
  vector<int> a(n), b(n);
  for(int i=0; i<n; i++) {
    cin >> a[i] >> b[i];
  }

  vector<int> diva = divisors(a[0]);
  vector<int> divb = divisors(b[0]);

  ll ans = 0;
  for(int da : diva) {
    for(int db : divb) {
      bool ok = true;
      for(int i=1; i<n; i++) {
        ok &= ((a[i] % da == 0 && b[i] % db == 0) ||
            (a[i] % db == 0 && b[i] % da == 0));
      }
      if(ok) {
        ans = max(ans, lcm((ll)da, (ll)db));
      }
    }
  }
  cout << ans << nl;

  return 0;
}
