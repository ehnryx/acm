#include <bits/stdc++.h>
using namespace std;

%:include "utility/fast_input.h"
%:include "utility/output.h"
%:include "math/number_theoretic_transform.h"
%:include "number/montgomery_int.h"
//%:include "number/mod_int.h"

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

using Int = montgomery_int<MOD>;
//using Int = mod_int<MOD>;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#ifdef USING_FAST_INPUT
  fast_input cin;
#endif

  int n, m;
  cin >> n >> m;
  auto a = cin.read<Int>(n);
  auto b = cin.read<Int>(m);
  cout << ntt::convolve<MOD>(a, b) << nl;

  //static_assert(Int::zero.v == 0);
  //static_assert(Int::one.value() == 1);
  //static_assert(Int::two.value() == 2);

  return 0;
}
