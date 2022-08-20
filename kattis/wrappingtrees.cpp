#include <bits/stdc++.h>
using namespace std;

%:include "utility/defines.h"
%:include "utility/fast_input.h"
%:include "utility/output.h"
%:include "geometry/convex_hull.h"

using ll = long long;
using ld = double;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

using pt = point<ll>;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#ifdef USING_FAST_INPUT
  fast_input cin;
#endif

  int n;
  cin >> n;
  auto g = cin.read<char>(n, n);

  if(n == 1) {
    cout << (g[0][0] == '1' ? 4 : 0) << nl;
    return 0;
  }

  vector<pt> v;
  int mid = (n-1) * (n-1);
  pt center(mid, mid);
  for(int i=0; i<n; i++) {
    for(int j=0; j<n; j++) {
      if(g[i][j] == '1') {
        pt pos(i, j);
        pos = center + (pos * 2 - center / (n-1)) * n;
        v.push_back(pos);
      }
    }
  }

  vector<pt> hull = convex_hull(v);
  int m = hull.size();
  ld ans = 0;
  for(int i=m-1, j=0; j<m; i=j++) {
    ans += (hull[i] - hull[j]).abs<ll>();
  }
  cout << ans / 2 / (n-1) << nl;

  return 0;
}
