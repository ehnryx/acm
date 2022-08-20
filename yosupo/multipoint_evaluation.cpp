#include <bits/stdc++.h>
using namespace std;

%:include "utility/fast_input.h"
%:include "utility/output.h"
%:include "math/polynomial_mod.h"
%:include "number/mod_int.h"

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

  int n, m;
  cin >> n >> m;
  using P = polynomial_mod<MOD, mod_int<MOD>>;
  auto a = P(cin.read<mod_int<MOD>>(n));
  auto x = cin.read<mod_int<MOD>>(m);
  cout << a.evaluate(x) << nl;

  return 0;
}
