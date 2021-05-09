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

  int n;
  cin >> n;
  vector<int> a(n), b(n), c(n), d(n);
  for(int i=0; i<n; i++) {
    cin >> a[i] >> b[i] >> c[i] >> d[i];
  }

  ld l = 0;
  ld r = 1e9;
  for(int bs=0; bs<99; bs++) {
    ld v = (l+r) / 2;
    ld ans = 0;
    for(int i=0; i<n; i++) {
      ans += max(b[i] - v*a[i], d[i] - v*c[i]);
    }
    if(ans < 0) {
      r = v;
    } else {
      l = v;
    }
  }
  cout << r << nl;

  return 0;
}
