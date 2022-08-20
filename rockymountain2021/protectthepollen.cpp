#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
//%:include "utility/output.h"

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

int solve(auto& adj, const auto& s, const auto& k,
    int u, int p, int i, int have, bool can, auto& dp) {
  if(!dp[u][have][can].empty() && dp[u][have][can][i] != -1) return dp[u][have][can][i];
  if(auto it = find(begin(adj[u]), end(adj[u]), p); it != end(adj[u])) {
    adj[u].erase(it);
  }

  dp[u][have][can].resize(size(adj[u]) + 1, -1);

  if(i == size(adj[u])) {
    int res = 0;
    if(empty(adj[u]) && can && s[u] <= have) {
      res = k[u];
    }
    return dp[u][have][can][i] = res;
  }

  int res = -1e-6;
  if(i == 0) {
    if(can) {
      for(int give=0; give <= have - s[u]; give++) {
        res = max(res, solve(adj, s, k, adj[u][i], u, 0, give, false, dp) +
            solve(adj, s, k, u, p, i+1, have - s[u] - give, false, dp) + k[u]);
      }
    }
    {
      for(int give=0; give<=have; give++) {
        res = max(res, solve(adj, s, k, adj[u][i], u, 0, give, true, dp) +
            solve(adj, s, k, u, p, i+1, have - give, true, dp));
      }
    }
  } else {
    for(int give=0; give<=have; give++) {
      res = max(res, solve(adj, s, k, adj[u][i], u, 0, give, can, dp) +
          solve(adj, s, k, u, p, i+1, have - give, can, dp));
    }
  }
  return dp[u][have][can][i] = res;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#ifdef USING_FAST_INPUT
  fast_input cin;
#endif

  int n, m;
  cin >> n >> m;
  vector<int> s(n+1), k(n+1);
  for(int i=1; i<=n; i++) {
    cin >> s[i] >> k[i];
  }
  vector<vector<int>> adj(n+1);
  for(int i=1; i<n; i++) {
    int a, b;
    cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }

  vector dp(n+1, vector(m+1, vector<vector<int>>(2)));
  cout << solve(adj, s, k, 1, 0, 0, m, true, dp) << nl;

  return 0;
}
