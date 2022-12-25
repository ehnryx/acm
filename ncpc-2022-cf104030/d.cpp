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


//#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  ll r;
  cin >> r;
  tuple<ll, ll, ll> ans(r*r*2, r, r);
  for(ll i=0; i<=r; i++) {
    ll x = r*r - i*i;
    ll s = sqrt(x);
    if(s*s <= x) s += 1;
    assert(s*s > x);
    ans = min(ans, tuple(s*s + i*i, i, s));
  }
  cout << get<1>(ans) << " " << get<2>(ans) << nl;
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
