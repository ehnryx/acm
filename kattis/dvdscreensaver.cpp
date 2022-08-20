#include <bits/stdc++.h>
using namespace std;

%:include "utility/fast_input.h"
%:include "utility/output.h"
%:include "math/extended_gcd.h"

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
#ifdef USING_FAST_INPUT
  fast_input cin;
#endif

  int T;
  cin >> T;
  while(T--) {
    int ws, hs, wl, hl, x, y;
    cin >> ws >> hs >> wl >> hl >> x >> y;
    int a = ws - wl;
    int b = hs - hl;
    int d = x - y;

    // solve for au - bv = d
    auto [g, u, v] = extended_gcd<ll>(a, b);
    if(d % g) {
      cout << "Johnny will die waiting" << nl;
      continue;
    }
    assert(u < 1<<30);
    assert(v < 1<<30);

    a /= g;
    b /= g;
    d /= g;
    u = u * d;
    v = -v * d;

    // min t st. u + t*b, v + t*a > 0
    ll t = max(-u / b, -v / a);
    u += t * b;
    v += t * a;

    ll A = a * g;
    ll B = b * g;
    while(A * u > x && B * v > y) {
      u -= b;
      v -= a;
    }
    while(A * u < x || B * v < y) {
      u += b;
      v += a;
    }

    cout << A * u - x << nl;
  }

  return 0;
}
