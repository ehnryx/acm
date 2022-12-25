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
  vector<double> a(n+1);
  for(int i=1; i<=n; i++) {
    cin >> a[i];
  }
  sort(begin(a) + 1, end(a), greater<>());

  double ans = 0;
  vector dp(2, vector<double>(2*n+3, 0.0));
  dp[0][0 + n+1] = 1;
  for(int i=1; i<=n; i++) {
    int id = i & 1;
    double pass = 0;
    for(int j=-i; j<=i; j++) {
      dp[id][j + n+1] = a[i] * dp[id^1][j-1 + n+1] + (1 - a[i]) * dp[id^1][j+1 + n+1];
      if(j >= m) {
        pass += dp[id][j + n+1];
      }
    }
    ans = max(ans, pass);
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
