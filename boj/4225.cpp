#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
//%:include "utility/output.h"

%:include "geometry/convex_hull.h"
%:include "geometry/lines.h"
%:include "geometry/point.h"

using ll = long long;
using ld = long double;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

using pt = point<double>;

//#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  for(int n, tt=1; cin >> n and n; tt++) {
    vector<pt> p;
    for(int i=0; i<n; i++) {
      double a, b;
      cin >> a >> b;
      p.emplace_back(a, b);
    }
    p = convex_hull<double>(EPS, p);
    n = size(p);
    double ans = 1e99;
    for(int i=n-1, j=0, k=0; j<n; i=j++) {
      while(true) {
        int nk = (k+1 == n ? 0 : k+1);
        auto dk = abs(line_point_dist(p[i], p[j], p[k]));
        auto dnk = abs(line_point_dist(p[i], p[j], p[nk]));
        if(dnk > dk) {
          k = nk;
        } else {
          break;
        }
      }
      ans = min(ans, abs(line_point_dist(p[i], p[j], p[k])));
    }
    cout << "Case " << tt << ": " << ans + 0.005 - EPS << nl;
  }
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(2);
#ifdef USING_FAST_INPUT
  fast_input cin;
#endif

  int T = 1;
#ifdef MULTI_TEST
  cin >> T;
#endif
  for(int testnum=1; testnum<=T; testnum++) {
    solve_main(testnum, cin);
  }

  return 0;
}
