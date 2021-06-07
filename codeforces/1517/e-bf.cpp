#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

//#define FILENAME sadcactus

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;
typedef long double ld;
typedef complex<ld> pt;

constexpr char nl = '\n';
constexpr ll INF = 0x3f3f3f3f;
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 998244353;
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
  while (T--) {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
      cin >> a[i];
    }

    int ans = 0;
    for (int bm = 0; bm < 1 << n; bm++) {
      vector<int> c, v;
      ll sum = 0;
      for (int i = 0; i < n; i++) {
        if (bm & 1 << i) {
          c.push_back(i);
          sum -= a[i];
        } else {
          v.push_back(i);
          sum += a[i];
        }
      }
      bool ok = (sum > 0);
      for (int i = 2; i < size(c); i++) {
        ok &= (c[i - 1] - c[i - 2] <= c[i] - c[i - 1]);
      }
      for (int i = 2; i < size(v); i++) {
        ok &= (v[i - 1] - v[i - 2] >= v[i] - v[i - 1]);
      }
      ans += ok;
    }
    cout << ans << nl;
  }

  return 0;
}
