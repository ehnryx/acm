#include <bits/stdc++.h>
using namespace std;

%:include "utility/fast_input.h"
%:include "utility/output.h"
%:include "geometry/point.h"
%:include "geometry/convex_hull.h"

using ll = long long;
using ld = double;
//using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

using pt = point<ld>;
const int M = 1e5;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#ifdef USING_FAST_INPUT
  fast_input cin;
#endif

  int n;
  cin >> n;
  string s;
  cin >> s;

  vector<pt> v;
  for(int i=0; i<n; i++) {
    pt lb = i;
    if(s[i] == 'T') {
      v.push_back(lb);
      v.push_back(lb + 1);
      v.push_back(lb + pt::polar(1, numbers::pi_v<pt::type> / 3));
    } else if(s[i] == 'S') {
      v.push_back(lb);
      v.push_back(lb + 1);
      v.push_back(lb + pt(0, 1));
      v.push_back(lb + pt(1, 1));
    } else {
      ld step = numbers::pi_v<pt::type> * 2 / M;
      for(int j=0; j<M; j++) {
        v.push_back(lb + pt(1, 1) / 2 + pt::polar((ld)1/2, j * step));
      }
    }
  }

  auto hull = convex_hull<pt::type>(1e-13L, v);
  n = hull.size();
  ld ans = 0;
  for(int i=n-1, j=0; j<n; i=j++) {
    ans += abs(hull[i] - hull[j]);
  }
  cout << ans << nl;

  return 0;
}
