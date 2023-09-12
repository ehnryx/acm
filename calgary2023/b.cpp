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

ll p10(int n) {
  ll ten = 1;
  for(int i=1; i<n; i++) {
    ten *= 10;
  }
  return ten;
}

ll solve(string_view s) {
  if(empty(s)) return 0;
  ll ten = p10(size(s));
  string nines(size(s) - 1, '9');
  if(s.front() == '7') {
    return (stoll("0" + string(s.substr(1))) + 1) + 7 * solve(nines);
  } else if(s.front() > '7') {
    return solve(s.substr(1)) + (s.front() - '0' - 1) * solve(nines) + ten;
  } else {
    return solve(s.substr(1)) + (s.front() - '0') * solve(nines);
  }
}

ll solve(ll n) {
  return solve(to_string(n));
}

//#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  ll a, b;
  cin >> a >> b;
  cout << solve(b) - solve(a - 1) << nl;
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
