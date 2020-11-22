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

  int _r, n, d, w;
  cin >> _r >> n >> d >> w;
  ld r = 1 + (ld)_r / 100;

  ld ans = 0;
  for(int k=0; k<=n; k++) {
    int t = n-k;
    ld rk = powl(r, k);
    ld rt = powl(r, t);
    ld lb = (1-rk) / (1-r) * w / rk;
    ld ub = (1-rt) / (1-r) * d * r;
    if(lb <= ub + d) {
      ans = max(ans, (ld)k*w - t*d + min((ld)w, ub-lb));
    }
  }
  cout << ans << nl;

  return 0;
}
