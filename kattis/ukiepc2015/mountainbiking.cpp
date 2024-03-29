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

  int n; ld g;
  cin >> n >> g;
  vector<ld> a(n), d(n);
  for(int i=0; i<n; i++) {
    int theta;
    cin >> d[i] >> theta;
    a[i] = g * cos(M_PIl * (ld)theta/180);
  }

  for(int i=0; i<n; i++) {
    ld v = 0;
    for(int j=i; j<n; j++) {
      // (1/2)at^2 + vt = s
      ld t = (-v + sqrt(v*v + 2*a[j]*d[j])) / a[j];
      v += a[j] * t;
    }
    cout << v << nl;
  }

  return 0;
}
