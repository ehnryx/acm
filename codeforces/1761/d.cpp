#include <bits/stdc++.h>
using namespace std;

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

//#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  int n, k;
  cin >> n >> k;

  vector<Int> p3(n+2);
  p3[0] = 1;
  for(int i=1; i<=n+1; i++) {
    p3[i] = p3[i-1] * 3;
  }

  vector<Int> f(n+2), invf(n+2);
  f[0] = 1;
  for(int i=1; i<=n+1; i++) {
    f[i] = f[i-1] * i;
  }
  invf[n+1] = f[n+1].inverse();
  for(int i=n; i>=0; i--) {
    invf[i] = invf[i+1] * (i+1);
  }
  assert(invf[0] == 1);

  if(k == 0) {
    return void(cout << Int(3).pow(n) << nl);
  }

  auto choose = [&](int a, int b) {
    if(b < 0 or a < b) return Int(0);
    return f[a] * invf[b] * invf[a-b];
  };

  Int ans = 0;
  for(int i=1; i<=k; i++) {
    if(n+1 - i >= k) {
      Int cur = p3[n+1 - 2*i] * choose(k - 1, i - 1) * choose(n+1 - k - 1, i - 1);
      ans += cur;
    }
    if(n - i >= k) {
      Int cur = p3[n - 2*i] * choose(k - 1, i - 1) * choose(n - k, i);
      ans += cur;
    }
  }
  cout << ans << nl;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#ifdef USING_FAST_INPUT
  fast_input cin;
#endif

  int T = 1;
#ifdef MULTI_TEST
  cin >> T;
#endif
  for(int testnum=1; testnum<=T; testnum++) {
    solve_main(testnum, cin);
  }

  return 0;
}
