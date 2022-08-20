#include <bits/stdc++.h>
using namespace std;

//%:include "utility/defines.h"
//%:include "utility/fast_input.h"
//%:include "utility/output.h"

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

  ll n; int b;
  cin >> n >> b;
  for(int i=0; i<=b; i++) {
    n -= 1LL << i;
  }
  cerr << " n = " << n << nl;
  cout << (n > 0 ? "no" : "yes") << nl;

  return 0;
}
