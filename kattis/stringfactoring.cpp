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
  string s;
  cin >> s;
  int n = size(s);
  vector dp(n, vector<int>(n, -1));

  auto solve = [&](auto&& self, int l, int r) -> int {
    if(l > r) return 0;
    if(dp[l][r] != -1) return dp[l][r];
    dp[l][r] = r - l + 1;
    for(int len = 1; len <= r - l + 1; len++) {
      string cur = s.substr(l, len);
      for(int i = 1; i*len <= r - l + 1 and cur == s.substr(l + len * (i-1), len); i++) {
        dp[l][r] = min(dp[l][r], self(self, l, l + len - 1) + self(self, l + i*len, r));
      }
    }
    return dp[l][r];
  };

  cout << solve(solve, 0, n-1) << nl;
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
