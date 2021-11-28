#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

const ld PI = acos((ld)-1);

ld sqr(ld x) {
  return x*x;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);

  ld a, b; int n;
  cin >> a >> b >> n;

  // we can decompose the pizza into a circle of radius b and an annulus part.
  // The annulus part decomposes into (1) a spiral with outer radius a and
  // (2) a right triangle with base 2pi*b and height a
  auto f = [=](ld x) {
    // circle + spiral + triangle
    return PI*sqr(b) * x + PI*sqr(a*x)/3 * x + (PI*b*x)*(a*x);
  };
  // also works: area ~ integral from 0 to theta of (b + ax/2pi)^2 dx

  ld total = f(1);
  for(int i=1; i<n; i++) {
    ld area = total * i/n;
    // binary search for the angle
    ld l = 0;
    ld r = 1;
    for(int bs=0; bs<99; bs++) {
      ld x = (l+r) / 2;
      if(f(x) < area) {
        l = x;
      } else {
        r = x;
      }
    }
    cout << r * 2*PI << nl;
  }

  return 0;
}
