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
  // f[i] = f[i-1] + 1 + p * (r + f[i])
  // f[i] = (f[i-1] + 1) / (1 - p)
  int n, t, r;
  cin >> n >> t >> r;
  ld p;
  cin >> p;
  // no save
  vector<ld> f(n+1);
  for(int i=1; i<=n; i++) {
    f[i] = (f[i-1] + 1 + p * r) / (1 - p);
  }
  // [last save]
  vector<ld> dp(n+1);
  for(int s=1; s<=n; s++) {
    dp[s] = f[s];
    for(int i=1; i<s; i++) {
      dp[s] = min(dp[s], dp[i] + f[s-i]);
    }
    dp[s] += t;
  }
  cout << dp[n] << nl;
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
