#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());


int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);

  int a, b, c, d;
  cin >> a >> b >> c >> d;
  ld e, f, g, h;
  cin >> e >> f >> g >> h;

  ld ylen2 = ((ld)e*e + (ld)f*f + (ld)g*g + (ld)h*h);
  e /= ylen2;
  f /= -ylen2;
  g /= -ylen2;
  h /= -ylen2;

  ld r = a*e - b*f - c*g - d*h;
  ld i = a*f + b*e + c*h - d*g;
  ld j = a*g - b*h + c*e + d*f;
  ld k = a*h + b*g - c*f + d*e;

  cout << r << " " << i << " " << j << " " << k << nl;

  return 0;
}
