#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
//%:include "utility/nd_array.h"
//%:include "utility/output.h"

%:include "geometry/convex_hull.h"

using ll = long long;
using ld = long double;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

using pt = point<int>;

//#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  int n;
  cin >> n;
  vector<pt> p;
  for(int i=0; i<n; i++) {
    int a, b;
    cin >> a >> b;
    p.emplace_back(a, b);
  }
  p = convex_hull(p);
  double ans = 0;
  for(int i=0; i<size(p); i++) {
    for(int j=0; j<i; j++) {
      ans = max(ans, abs(p[i] - p[j]));
    }
  }
  cout << ans << nl;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
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
