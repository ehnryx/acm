#include <bits/stdc++.h>
using namespace std;

%:include "io/fast_input.h"

%:include "number/int_base10.h"

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

using Int = int_base10;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(4);
#ifdef USING_FAST_INPUT
  fast_input cin;
#endif

  int n;
  cin >> n;
  vector<Int> x(n), y(n);
  for(int i=0; i<n; i++) {
    cin >> x[i] >> y[i];
  }

  Int dx = 0;
  Int dy = 0;
  Int dxy = 0;
  Int dxx = 0;
  Int dyy = 0;
  Int dxxy = 0;
  Int dyyx = 0;
  Int dxxyy = 0;
  for(int i=0; i<n; i++) {
    dx += x[i];
    dy += y[i];
    dxy += x[i] * y[i];
    dxx += x[i] * x[i];
    dyy += y[i] * y[i];
    dxxy += x[i] * x[i] * y[i];
    dyyx += x[i] * y[i] * y[i];
    dxxyy += x[i] * x[i] * y[i] * y[i];
  }

  Int xx_yy = dxx * dyy - dxxyy;

  Int x_y = dx * dy - dxy;
  Int xxy_y = dxxy * dy - dxxyy;
  Int yyx_x = dyyx * dx - dxxyy;
  Int xy_x_y = dxy * x_y - xxy_y - yyx_x;

  Int x_x_2 = dx * dx - dxx;
  Int y_y_2 = dy * dy - dyy;
  Int xx_y_y_2 = dxx * y_y_2 - xxy_y * 2;
  Int yy_x_x_2 = dyy * x_x_2 - yyx_x * 2;

  Int xy_xy = dxy * dxy - dxxyy;

  Int area =
    xx_yy * (n-2)
    + xy_x_y * 2
    - xx_y_y_2
    - yy_x_x_2
    - xy_xy * (n-2);

  auto [ans, rem] = area.divide_remainder(4);
  cout << ans << "." << (rem == 0 ? "0000" : rem == 1 ? "2500" : rem == 2 ? "5000" : "7500") << nl;

  return 0;
}
