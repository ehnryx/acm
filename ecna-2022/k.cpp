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
  int n, m;
  cin >> n >> m;
  vector dp(m, vector<int>(n+1));
  for(int i=0; i<=n; i++) {
    dp[0][i] = i;
  }
  for(int j=1; j<m; j++) {
    for(int i=1; i<=n; i++) {
      dp[j][i] = n;
      for(int k=1; k<=i; k++) {
        int val = 1 + max(dp[j-1][k-1], dp[j][i-k]);
        dp[j][i] = min(dp[j][i], val);
      }
    }
  }

  cout << dp.back()[n] << " ";
  if(m == 1) {
    cout << 1 << nl;
  } else {
    int first = 0;
    int last = 0;
    for(int k=1; k<=n; k++) {
      int val = 1 + max(dp[m-2][k-1], dp[m-1][n-k]);
      if(val == dp.back()[n]) {
        if(first == 0) first = k;
        last = k;
      }
    }
    if(first == last) {
      cout << first << nl;
    } else {
      cout << first << "-" << last << nl;
    }
  }
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
