#include <bits/stdc++.h>
using namespace std;

#include "../../lca/number/mod_int.h"
#include "../../lca/number/int_base10.h"

const char nl = '\n';
using ll = long long;
using ld = long double;

using Int = mod_int<998244353>;

Int solve(const string& s) {
  int n = s.size();
  vector dp(n, vector(10, vector(2, vector<Int>(2)))); // pos, digit, lead?, follow?
  dp[0][0][true][true] = 1;
  for (int i = 1; i < n; i++) {
    // leading zero
    dp[i][0][true][false] = dp[i - 1][0][true][false] + dp[i - 1][0][true][true];
    // follow
    if (s[i] != s[i - 1]) {
      dp[i][s[i] - '0'][false][true] =
        dp[i - 1][s[i - 1] - '0'][false][true] + dp[i - 1][s[i - 1] - '0'][true][true];
    }
    // add digit
    for (int d = 0; d <= 9; d++) {
      for (int pd = 0; pd <= 9; pd++) {
        if (d == pd) continue;
        dp[i][d][false][false] += dp[i - 1][pd][false][false] + dp[i - 1][pd][true][false];
        if (d < s[i] - '0') {
          dp[i][d][false][false] += dp[i - 1][pd][false][true] + dp[i - 1][pd][true][true];
        }
      }
    }
  }
  Int ans = 0;
  for (int d = 0; d <= 9; d++) {
    for (int lead = 0; lead < 2; lead++) {
      for (int follow = 0; follow < 2; follow++) {
        ans += dp[n - 1][d][lead][follow];
      }
    }
  }
  return ans;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  string left, right;
  cin >> left >> right;
  cout << solve("0" + right) - solve("0" + (int_base10(left) - 1).str()) << nl;

  return 0;
}
