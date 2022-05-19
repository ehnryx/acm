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

  function<ld(ld)> value = [a,b,c,d](ld x) {
    return max(x*x + a*x + b, x*x + c*x + d);
  };

  ld l = -1e9;
  ld r = 1e9;
  for(int it=0; it<1e4; it++) {
    ld lm = (5*l + 4*r) / 9;
    ld rm = (5*r + 4*l) / 9;
    if(value(lm) < value(rm)) {
      r = rm;
    } else {
      l = lm;
    }
  }
  r = (l + r) / 2;
  cout << r << " " << value(r) << nl;

  return 0;
}
