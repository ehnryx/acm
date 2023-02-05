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
  int n;
  cin >> n;
  vector<bool> same(n);
  vector<int> left(n, -1);
  for(int i=0; i<n; i++) {
    for(int j=i; j<n; j++) {
      int v;
      cin >> v;
      if(v == 1) {
        for(int k=i+1; k<=j; k++) {
          same[k] = true;
        }
      } else if(v == 2) {  
        left[j] = max(left[j], i);
      }
    }
  }

  vector<Int> dp(n+1);
  dp[0] = 1;
  for(int i=0; i<n; i++) {
    for(int j=i, lb=left[i]; j>lb; j--) {
      if(not same[j]) {
        dp[i+1] += dp[j];
      }
      lb = max(lb, left[j-1]);
    }
  }
  cout << dp[n] * 2 << nl;
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
