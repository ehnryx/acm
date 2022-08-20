#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
//%:include "utility/output.h"

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

ll solve(ll n, ll v) {
  if(v == 0) return 0;
  int len = to_string(n).size();
  int d = to_string(v).size();
  ll s = 0;
  ll ten = llround(powl(10, d));
  ll res = 0;
  for(int i=0; i<len/d; i++) {
    s = s * ten + v;
    if(i > 0 && s <= n) {
      res = max(res, s);
    }
  }
  return res;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#ifdef USING_FAST_INPUT
  fast_input cin;
#endif

  int T;
  cin >> T;
  while(T--) {
    ll n;
    cin >> n;
    string s = to_string(n);
    int len = s.size();
    ll ans = llround(powl(10, len - 1)) - 1;
    for(int d=1; d<len; d++) {
      ll v = stoll(s.substr(0, d));
      ans = max(ans, solve(n, v));
      ans = max(ans, solve(n, v - 1));
    }
    assert(ans && ans >= 11);
    cout << ans << nl;
  }

  return 0;
}
