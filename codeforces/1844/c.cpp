#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
//%:include "utility/output.h"

%:include "utility/nd_array.h"

using ll = long long;
using ld = long double;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());


#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  int n;
  cin >> n;
  vector<int> a(n+1);
  for(int i=1; i<=n; i++) {
    cin >> a[i];
  }
  ll ans = *max_element(begin(a) + 1, end(a));
  if(ans <= 0) {
    return void(cout << ans << nl);
  }

  nd_array<ll, 2> dp(n+1, 2);
  for(int i=1; i<=n; i++) {
    dp(i, 0) = dp(i-1, 1);
    dp(i, 1) = dp(i-1, 0) + max(0, a[i]);
  }
  cout << max({dp(n, 0), dp(n, 1), ans}) << nl;
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
