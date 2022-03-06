#include <bits/stdc++.h>
using namespace std;

#include "../../lca/graph/two_sat.h"

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
  vector g(n, vector<char>(m));
  set<pair<int, int>> edges;
  for(int i=0; i<n; i++) {
    for(int j=0; j<m; j++) {
      cin >> g[i][j];
      if(g[i][j] == 'X') continue;
      for(int k=0; k<j; k++) {
        if(g[i][k] == 'X') continue;
        int matchj = 2*j + (g[i][j] == 'F');
        int matchk = 2*k + (g[i][k] == 'F');
        edges.insert(pair(matchj, matchk ^ 1));
        edges.insert(pair(matchk, matchj ^ 1));
      }
    }
  }

  two_sat key(m);
  for(auto [a, b] : edges) {
    key.add_edge(a, b);
    //cerr << "add edge " << a << " -> " << b << nl;
  }

  string ans;
  for(int i=0; i<m; i++) {
    key.add_edge(2*i, 2*i + 1);  // force F
    if (key.solve()) {
      ans.push_back('F');
    } else {
      key.adj[2*i].pop_back();
      key.add_edge(2*i + 1, 2*i);  // force T
      if (key.solve()) {
        ans.push_back('T');
      } else {
        cout << -1 << nl;
        return 0;
      }
    }
  }
  cout << ans << nl;

  return 0;
}
