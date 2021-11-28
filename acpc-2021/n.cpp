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

  vector<int> dsu(n+1);
  function<int(int)> find = [&](int i) {
    if(dsu[i] == 0) return i;
    return dsu[i] = find(dsu[i]);
  };
  auto link = [&](int i, int j) {
    if(find(i) != find(j)) {
      dsu[find(i)] = find(j);
      return true;
    }
    return false;
  };

  // a spanning forest is sufficient
  vector<vector<int>> adj(n+1);
  for(int i=0; i<m; i++) {
    int a, b;
    cin >> a >> b;
    if(link(a, b)) {
      adj[a].push_back(b);
      adj[b].push_back(a);
    }
  }

  vector<int> val(n+1);
  for(int i=1; i<=n; i++) {
    cin >> val[i];
    if(find(val[i]) != find(i)) {
      cout << "impossible" << nl;
      return 0;
    }
  }

  vector<pair<int, int>> ans;

  vector<int> num(n+1);
  iota(begin(num), end(num), 0);

  // move to correct place
  function<bool(int, int, int)> solve = [&](int u, int p, int want) {
    if(num[u] == want) return true;
    for(int v : adj[u]) {
      if(v == p) continue;
      if(solve(v, u, want)) {
        ans.emplace_back(num[v], num[u]);
        swap(num[v], num[u]);
        return true;
      }
    }
    return false;
  };

  // go in toposort order
  function<void(int, int)> dfs = [&](int u, int p) {
    for(int v : adj[u]) {
      if(v == p) continue;
      dfs(v, u);
    }
    solve(u, 0, val[u]);
  };

  for(int i=1; i<=n; i++) {
    if(find(i) != i) continue;
    dfs(i, 0);
  }

  cout << ans.size() << nl;
  for(auto [a, b] : ans) {
    cout << a << " " << b << nl;
  }

  return 0;
}
