#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
%:include "utility/output.h"
%:include "number/int_base10.h"

using ll = long long;
using ld = long double;

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

  // 2 + (1 + 3/2 + 9/4 + ... + 3^k/2^k + ...)
  // 2 + ((3/2)^(n+1) - 1) / (3/2 - 1)
  // 2 + (3^(n+1) / 2^n - 2) / (3 - 2)
  // 3^(n+1) / 2^n

  for(int tt=1, n; cin >> n; tt++) {
    auto ans = int_base10(3).pow(n+1) / int_base10(2).pow(n);
    cout << "Case " << tt << ": " << ans.length() << nl;
  }

  return 0;
}
