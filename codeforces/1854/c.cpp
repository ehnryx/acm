#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
//%:include "utility/output.h"

%:include "number/mod_int.h"

using ll = long long;
using ld = long double;

constexpr char nl = '\n';
constexpr int MOD = 1e9 + 7;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

using Int = mod_int<MOD>;

//#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  int n, m;
  cin >> n >> m;

  vector ncr(2*m+1, vector<Int>(2*m+1));
  for(int i=0; i<=2*m; i++) {
    ncr[i][0] = ncr[i][i] = 1;
    for(int j=1; j<i; j++) {
      ncr[i][j] = ncr[i-1][j] + ncr[i-1][j-1];
    }
  }

  vector<Int> p2(2*m+1);
  p2[0] = 1;
  for(int i=1; i<=2*m; i++) {
    p2[i] = p2[i-1] + p2[i-1];
  }

  vector<int> a(n+1);
  for(int i=1; i<=n; i++) {
    cin >> a[i];
  }

  vector memo(m, vector<Int>(m));
  for(int d=1; d<m; d++) {
    for(int s=0; d+s<=m; s++) {
      memo[d][s] = ncr[d+2*s][s];
      for(int i=0; i<s; i++) {
        memo[d][s] -= memo[d][i] * ncr[2*(s-i)][s-i];
      }
    }
  }

  Int ans = m - a[n] + 1;
  for(int i=1; i<n; i++) {
    int d = a[i+1] - a[i];
    Int tot = 0;
    for(int s=0; s+a[i+1]<=m; s++) {
      Int num = memo[d][s];
      Int den = p2[d + 2*s];
      Int cur = num / den;
      tot += cur;
      ans += cur * (d + s);
    }
    Int rem = Int(1) - tot;
    ans += rem * (m+1 - a[i]);
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
