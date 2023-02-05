#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
//%:include "utility/output.h"

%:include "string/kmp_matching.h"

using ll = long long;
using ld = long double;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

struct to_int {
  static constexpr int size = 26;
  int operator()(char c) const { return c - 'a'; }
};

//#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  string s, a, b;
  cin >> s >> a >> b;
  auto dfa = kmp_matching(a).template build_dfa<to_int>();
  auto dfb = kmp_matching(b).template build_dfa<to_int>();

  static constexpr int big = numeric_limits<int>::max();
  vector dp(size(s) + 1, vector(dfa.size(), vector(dfb.size(), -big)));
  dp[0][0][0] = 0;
  for(int i=0; i<size(s); i++) {
    for(char c='a'; c<='z'; c++) {
      if(not (s[i] == '*' or s[i] == c)) continue;
      int ci = to_int()(c);
      for(int j=0; j<dfa.size(); j++) {
        for(int k=0; k<dfb.size(); k++) {
          if(dp[i][j][k] == big) continue;
          int nj = dfa[j][ci];
          int nk = dfb[k][ci];
          dp[i+1][nj][nk] = max(dp[i+1][nj][nk],
              dp[i][j][k] + (nj == size(a)) - (nk == size(b)));
        }
      }
    }
  }

  int ans = -big;
  for(int j=0; j<dfa.size(); j++) {
    for(int k=0; k<dfb.size(); k++) {
      ans = max(ans, dp[size(s)][j][k]);
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
