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

  int n, m;
  cin >> n >> m;
  vector<vector<pair<int, int>>> adj(n);
  for(int i=1; i<n; i++) {
    int a, b, c;
    cin >> a >> b >> c;
    adj[a].emplace_back(b, c);
    adj[b].emplace_back(a, c);
  }
  vector<int> have(n);
  for(int i=0; i<m; i++) {
    int v;
    cin >> v;
    have[v] = true;
  }

  function<pair<int, bool>(int, int)> solve = [&](int u, int p) {
    if(p != -1) adj[u].erase(find_if(begin(adj[u]), end(adj[u]),
          [p](pair<int, int> it) { return it.first == p; } ));
    bool has_leaf = have[u];
    int res = 0;
    for(auto [v, c] : adj[u]) {
      auto [dist, has] = solve(v, u);
      res += dist;
      if(has) res += 2*c;
      has_leaf |= has;
    }
    return pair(res, has_leaf);
  };

  cout << solve(0, -1).first << nl;

  return 0;
}
