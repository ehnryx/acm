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


int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#ifdef USING_FAST_INPUT
  fast_input cin;
#endif

  int n;
  cin >> n;
  vector<int> t(n + 1);
  for(int i=1; i<=n; i++) {
    cin >> t[i];
  }
  vector<vector<pair<int, int>>> adj(n + 1);
  for(int i=1; i<n; i++) {
    int a, b, c;
    cin >> a >> b >> c;
    adj[a].emplace_back(b, c);
    adj[b].emplace_back(a, c);
  }

  vector<int> s(n + 1);
  vector<int> ts(n + 1);

  ll sumd = 0;
  ll sumt = 0;
  auto build = [&](auto& self, int u, int p, int d) -> void {
    sumd += d;
    sumt += d * (ll)t[u];
    s[u] = 1;
    ts[u] = t[u];
    for(auto [v, c] : adj[u]) {
      if(v == p) continue;
      self(self, v, u, d + c);
      s[u] += s[v];
      ts[u] += ts[v];
    }
  };
  build(build, 1, 0, 0);

  vector<ll> ans(n + 1);
  auto solve = [&](auto& self, int u, int p) -> void {
    ans[u] = sumd * t[u] + sumt;
    for(auto [v, c] : adj[u]) {
      if(v == p) continue;
      sumd += ((n - s[v]) - s[v]) * (ll)c;
      sumt += ((ts[1] - ts[v]) - ts[v]) * (ll)c;
      self(self, v, u);
      sumd -= ((n - s[v]) - s[v]) * (ll)c;
      sumt -= ((ts[1] - ts[v]) - ts[v]) * (ll)c;
    }
  };
  solve(solve, 1, 0);

  for(int i=1; i<=n; i++) {
    cout << ans[i] << nl;
  }

  return 0;
}
