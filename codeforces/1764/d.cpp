#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
//%:include "utility/output.h"

using ll = long long;
using ld = long double;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

ll power(ll n, int e, int mod) {
  ll r = 1;
  for(; e; e/=2) {
    if(e & 1) r = r*n % mod;
    n = n*n % mod;
  }
  return r;
}

ll inverse(ll n, int mod) {
  return power(n, mod - 2, mod);
}

//#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  int n, mod;
  cin >> n >> mod;

  vector<ll> f(n+1), invf(n+1);
  f[0] = 1;
  for(int i=1; i<=n; i++) {
    f[i] = f[i-1] * i % mod;
  }
  invf[n] = inverse(f[n], mod);
  for(int i=n; i>=1; i--) {
    invf[i-1] = invf[i] * i % mod;
  }
  assert(invf[0] == f[0]);

  auto choose = [&](int N, int R) {
    if(R < 0 or N < R) return 0ll;
    return f[N] * invf[R] % mod * invf[N - R] % mod;
  };

  ll ans = 0;

  int h = n / 2;
  if(n % 2 == 0) {
    for(int r=2; r<=h; r++) {
      for(int k=2; k<=r; k++) {
        ll cur = r * f[n - k - 1] % mod * choose(r-2, k-2) % mod;
        ll add = cur * n % mod;
        ans += add;
      }
    }
    ans += n * f[n - 2] % mod;
  } else {
    assert(n == 2*h + 1);
    for(int r=1; r<=h; r++) {
      for(int k=1; k<=r; k++) {
        ll cur = r * f[n - k - 2] % mod * choose(r-1, k-1) % mod;
        ll add = cur * n % mod;
        ans += add;
      }
    }
  }

  cout << ans % mod << nl;
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
