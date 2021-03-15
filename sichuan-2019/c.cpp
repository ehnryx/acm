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
typedef double ld;
typedef complex<ld> pt;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 998244353;
const ld EPS = 1e-11;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

void solve() {
  int n, m;
  ld A, B;
  cin >> n >> m >> A >> B;
  //scanf("%d %d %lf %lf", &n, &m, &A, &B);
  vector<ld> x(n), xs(n+1);
  for(int i=0; i<n; i++) {
    cin >> x[i];
    //scanf("%lf", &x[i]);
  }
  sort(x.begin(), x.end());
  partial_sum(x.begin(), x.end(), xs.begin() + 1);

  for(int i=0; i<m; i++) {
    ld c, d;
    cin >> c >> d;
    //scanf("%lf %lf", &c, &d);
    ld res = 0;
    if(abs(A*c - 1) < EPS) {
      res += n * abs(A*d + B);
      res += n * abs(B*c + d);
    } else {
      // f(g(x)) - x
      ld xsplit = (A*d + B) / (1 - A*c);
      int mid = lower_bound(x.begin(), x.end(), xsplit) - x.begin();
      if(A*c - 1 < 0) {
        res += A*c * (xs[mid] - xs.front()) + (A*d + B) * mid - (xs[mid] - xs.front());
        res -= A*c * (xs.back() - xs[mid]) + (A*d + B) * (n - mid) - (xs.back() - xs[mid]);
      } else {
        res -= A*c * (xs[mid] - xs.front()) + (A*d + B) * mid - (xs[mid] - xs.front());
        res += A*c * (xs.back() - xs[mid]) + (A*d + B) * (n - mid) - (xs.back() - xs[mid]);
      }
      // g(f(x)) - x
      xsplit = (B*c + d) / (1 - A*c);
      mid = lower_bound(x.begin(), x.end(), xsplit) - x.begin();
      if(A*c - 1 < 0) {
        res += A*c * (xs[mid] - xs.front()) + (c*B + d) * mid - (xs[mid] - xs.front());
        res -= A*c * (xs.back() - xs[mid]) + (c*B + d) * (n - mid) - (xs.back() - xs[mid]);
      } else {
        res -= A*c * (xs[mid] - xs.front()) + (c*B + d) * mid - (xs[mid] - xs.front());
        res += A*c * (xs.back() - xs[mid]) + (c*B + d) * (n - mid) - (xs.back() - xs[mid]);
      }
    }
    cout << res << nl;
  }
}

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

  int T;
  cin >> T;
  //scanf("%d", &T);
  for(int tt=1; tt<=T; tt++) {
    cout << "Case " << tt << ":" << nl;
    solve();
  }

  return 0;
}
