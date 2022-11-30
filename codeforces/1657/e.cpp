#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
//%:include "utility/output.h"

%:include "number/mod_int.h"

using ll = long long;
using ld = long double;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

using Int = mod_int<MOD>;

//#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  int n, k;
  cin >> n >> k;

  vector ncr(n+1, vector<Int>(n+1));
  for(int i=0; i<=n; i++) {
    ncr[i][0] = ncr[i][i] = 1;
    for(int j=1; j<i; j++) {
      ncr[i][j] = ncr[i-1][j] + ncr[i-1][j-1];
    }
  }

  vector pk(k+1, vector<Int>(n * (n-1) / 2 + 1));
  for(int i=1; i<=k; i++) {
    pk[i][0] = 1;
    for(int j=1; j<size(pk[i]); j++) {
      pk[i][j] = pk[i][j-1] * i;
    }
  }

  n -= 1; // exclude 1

  vector dp(k+1, vector<Int>(n+1));
  dp[0][0] = 1;
  for(int i=1; i<=k; i++) {
    for(int j=0; j<=n; j++) {
      for(int t=0; t<=j; t++) {
        // choose t of n-j+t to have value k
        int edges = t * (t-1) / 2 + t * (n-j);
        dp[i][j] += dp[i-1][j-t] * ncr[n-j+t][t] * pk[i][edges];
      }
    }
  }

  cout << dp[k][n] << nl;
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
