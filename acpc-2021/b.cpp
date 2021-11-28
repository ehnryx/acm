#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());


int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);

  int n;
  cin >> n;
  vector<int> a(3*n + 1);
  for(int i=1; i<=3*n; i++) {
    cin >> a[i];
  }

  vector<int> sum;
  partial_sum(begin(a), end(a), back_inserter(sum));

  // dp[i][j][k] = expected extra score given that we have
  // i bins with 0 balls, j bins with 1 ball, and k bins with 2 balls.
  // The # of bins with 3 balls is implicit (n - i - j - k)
  // We choose whether we throw the bth or not. If we throw, then we
  // either add the value bth ball plus whatever we get from that state onwards,
  // or we lose all that we had.
  vector dp(n+1, vector(n+1, vector<ld>(n+1)));
  for(int i=0; i<=n; i++) {
    for(int j=0; i+j<=n; j++) {
      for(int k=0; i+j+k<=n; k++) {
        int balls = j + 2*k + 3*(n-i-j-k);
        // base case = 0
        if(balls == 3*n) continue;
        // calculate expected extra score if we throw
        ld val = (ld)(n-i-j-k)/n * -sum[balls];
        if(i > 0) val += (ld)i/n * (dp[i-1][j+1][k] + a[balls + 1]);
        if(j > 0) val += (ld)j/n * (dp[i][j-1][k+1] + a[balls + 1]);
        if(k > 0) val += (ld)k/n * (dp[i][j][k-1] + a[balls + 1]);
        // we only want to throw if the expected value is positive
        dp[i][j][k] = max((ld)0, val);
      }
    }
  }
  // initial state has n empty bins
  cout << dp[n][0][0] << nl;

  return 0;
}
