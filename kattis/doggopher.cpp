#include <bits/stdc++.h>
using namespace std;

%:include "io/fast_input.h"

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());


int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(3);
#ifdef USING_FAST_INPUT
  fast_input cin;
#endif

  pt g, d;
  cin >> g >> d;

  for(pt x; cin >> x; ) {
    if(2 * abs(x - g) < abs(x - d) + EPS) {
      cout << "The gopher can escape through the hole at (" << x.real() << "," << x.imag() << ")." << nl;
      return 0;
    }
  }
  cout << "The gopher cannot escape." << nl;

  return 0;
}
