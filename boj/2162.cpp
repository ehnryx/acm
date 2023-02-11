#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
//%:include "utility/output.h"

%:include "geometry/lines.h"
%:include "geometry/point.h"
%:include "ds/union_find.h"

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
  union_find<> dsu(n);
  vector<pair<pt, pt>> segs;
  for(int i=0; i<n; i++) {
    int a, b, x, y;
    cin >> a >> b >> x >> y;
    pt u(a, b), v(x, y);
    for(int j=0; j<i; j++) {
      if(seg_x_seg(u, v, segs[j].first, segs[j].second)) {
        dsu.link(i, j);
      }
    }
    segs.emplace_back(u, v);
  }
  int ans = 0;
  int res = 0;
  for(int i=0; i<n; i++) {
    if(dsu[i] == i) {
      ans++;
      res = max(res, dsu.size(i));
    }
  }
  cout << ans << nl;
  cout << res << nl;
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
