#include <bits/stdc++.h>
using namespace std;

//%:include "utility/defines.h"
//%:include "utility/fast_input.h"
//%:include "utility/output.h"

%:include "number/mod_int.h"

using ll = long long;
using ld = long double;

constexpr char nl = '\n';
constexpr int MOD = 1e9 + 7;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

using Int = mod_int<MOD>;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#ifdef USING_FAST_INPUT
  fast_input cin;
#endif

  const int M = 4e5 + 7;
  vector<Int> fact(M), invf(M);
  fact[0] = 1;
  for(int i=1; i<M; i++) {
    fact[i] = fact[i-1] * i;
  }
  invf[M-1] = fact[M-1].inverse();
  for(int i=M-1; i>0; i--) {
    invf[i-1] = invf[i] * i;
  }
  assert(invf[0] == 1);

  auto value = [&](int i, int j) -> Int {
    if(i<0 || j<0) return 0;
    return fact[i+j] * invf[i] * invf[j];
  };

  int n;
  cin >> n;
  vector<int> a(n+1);
  Int ans = 0;
  for(int i=0; i<=n; i++) {
    cin >> a[i];
    ans += value(i + 1, a[i] - 1);
  }
  cout << ans << nl;

  return 0;
}
