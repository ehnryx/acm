#include <bits/stdc++.h>
using namespace std;

%:include "utility/fast_input.h"
%:include "utility/output.h"
%:include "geometry/point.h"
%:include "geometry/convex_hull.h"

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

using P = point<ll>;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#ifdef USING_FAST_INPUT
  fast_input cin;
#endif

  int n;
  cin >> n;
  auto v = cin.read<P>(n);
  vector<ld> dist(1<<n);
  for(int bm=0; bm<1<<n; bm++) {
    vector<P> sub;
    for(int i=0; i<n; i++) {
      if(bm & 1<<i) {
        sub.push_back(v[i]);
      }
    }
    sub = convex_hull(sub);
    for(int i=(int)sub.size()-1, j=0; j<sub.size(); i=j++) {
      dist[bm] += abs(sub[i] - sub[j]);
    }
  }

  vector<ld> ans(1<<n, 1e42);
  ans[0] = 0;
  for(int bm=1; bm<1<<n; bm++) {
    for(int sm=bm; sm; sm=(sm-1)&bm) {
      if(__builtin_popcount(sm) < 3) continue;
      ans[bm] = min(ans[bm], ans[bm^sm] + dist[sm]);
    }
  }
  cout << ans[(1<<n) - 1] << nl;

  return 0;
}
