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
  // p = value, c = cost
  // max (sum_u p_u) / (sum_u c_u)
  // suppose (sum_u p_u) / (sum_u c_u) >= A
  //  sum_u p_u >= A * sum_u c_u
  //  sum_u p_u - A * sum_u c_u >= 0
  // maximize sum_u p_u - A * sum_u c_u
  int k, n;
  cin >> k >> n;
  vector<vector<int>> adj(n+1);
  vector<int> p(n+1), c(n+1);
  static constexpr int M = 2000;
  for(int i=1; i<=n; i++) {
    int ref;
    cin >> c[i] >> p[i] >> ref;
    p[i] *= M;
    adj[ref].push_back(i);
  }

  int l = 0;
  int r = 1e7;
  while(l < r) {
    int A = (l + r + 1) / 2;

    vector<vector<ll>> dp(n+1);
    auto solve = [&](auto&& self, int u) -> void {
      vector<ll> cdp = { p[u] - c[u] * (ll)A };
      for(int v : adj[u]) {
        self(self, v);
        static constexpr ll big = 1ll << 60;
        int cur = size(cdp);
        cdp.resize(cur + size(dp[v]), -big);
        for(int i=cur-1; i>=0; i--) {
          for(int j=0; j<size(dp[v]); j++) {
            cdp[i + j + 1] = max(cdp[i + j + 1], cdp[i] + dp[v][j]);
          }
        }
      }
      dp[u] = move(cdp);
    };

    solve(solve, 0);
    if(dp[0][k] >= 0) {
      l = A;
    } else {
      r = A - 1;
    }
  }

  cout << r / M << "." << setw(3) << setfill('0') << (r % M + 1) / 2 << nl;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(3);
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
