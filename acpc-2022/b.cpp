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
  int n, k;
  cin >> n >> k;
  vector<vector<int>> adj(n+1);
  for(int i=1; i<n; i++) {
    int a, b;
    cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }

  if(k == 1) {
    if(n == 1) {
      cout << 1 << nl;
    } else {
      cout << -1 << nl;
    }
    return;
  }

  vector dp(n+1, vector<int>(k, -1));
  auto solve = [&](auto&& self, int u, int p, int val) {
    if(dp[u][val] != -1) {
      return dp[u][val];
    }
    int res = val + 1;
    for(int v : adj[u]) {
      if(v == p) continue;
      int best = numeric_limits<int>::max();
      for(int give=0; give<k; give++) {
        if(give == val) continue;
        best = min(best, self(self, v, u, give));
      }
      res += best;
    }
    return dp[u][val] = res;
  };

  int best = numeric_limits<int>::max();
  for(int i=0; i<k; i++) {
    best = min(best, solve(solve, 1, 0, i));
  }
  cout << best << nl;
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
