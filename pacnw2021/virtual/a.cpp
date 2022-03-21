#include <bits/stdc++.h>
using namespace std;

#include "../../lca/number/mod_int.h"

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int MOD = 1e9 + 7;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

using Int = mod_int<MOD>;

struct Angle {
  Int c, s;
  Angle operator + (const Angle& o) const { return Angle(*this) += o; }
  Angle& operator += (const Angle& o) {
    Int nc = c*o.c - s*o.s;
    s = c*o.s + s*o.c;
    c = nc;
    return *this;
  }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);

  ll a, b, n;
  cin >> a >> b >> n;

  // tan x = b/a , want -cos(2nx)
  Angle cs = {
    Int(2) * a*a / (Int(a)*a + Int(b)*b) - 1,
    Int(2) * a*b / (Int(a)*a + Int(b)*b),
  };
  Angle ans = { -1, 0 };
  for(n += 1; n; n/=2) {
    if(n&1) ans += cs;
    cs += cs;
  }
  cout << ans.c << nl;

  return 0;
}
