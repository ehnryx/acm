//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
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

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 998244353;
const ld EPS = 1e-9;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());



// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);
#if defined(ONLINE_JUDGE) && defined(FILENAME)
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif

  int n;
  cin >> n;
  vector<int> d(n), a(n);
  for(int i=0; i<n; i++) {
    cin >> d[i] >> a[i];
  }

  ld ans = -1;
  function<bool(ld)> valid = [&](ld v) {
    ans = 0;
    for(int i=0; i<n; i++) {
      ld A = (ld) a[i] / 2;
      ld B = v;
      ld C = -d[i];
      ld D = B*B - 4*A*C;
      if(D < 0) return false;
      ld t = (A ? (-B + sqrt(D)) / (2*A) : d[i] / v);
      v += a[i]*t;
      assert(v >= 0);
      ans += t;
    }
    return true;
  };

  ld l = 0;
  ld r = 1e4;
  for(int bs=0; bs<200; bs++) {
    ld m = (l+r) / 2;
    if(valid(m)) {
      r = m;
    } else {
      l = m;
    }
  }
  assert(valid(r));
  cout << r << " " << ans << nl;
  assert(ans >= 0);

  return 0;
}
