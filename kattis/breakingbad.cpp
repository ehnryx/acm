#include <bits/stdc++.h>
using namespace std;

%:include "graph/graph.h"

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
  vector<string> names(n);
  unordered_map<string, int> remap;
  for(int i=0; i<n; i++) {
    cin >> names[i];
    remap[names[i]] = i;
  }

  graph_list<void> graph(n);

  int m;
  cin >> m;
  for(int i=0; i<m; i++) {
    string a, b;
    cin >> a >> b;
    graph.add_edge(remap[a], remap[b]);
    graph.add_edge(remap[b], remap[a]);
  }

  vector<int> ans(n, -1);
  function<bool(int,int)> dfs = [&](int u, int t) {
    ans[u] = t;
    for(int v : graph[u]) {
      if(ans[v] == -1) {
        if(!dfs(v, t^1)) {
          return false;
        }
      } else if(ans[v] == t) {
        return false;
      }
    }
    return true;
  };

  for(int i=0; i<n; i++) {
    if(ans[i] == -1 && !dfs(i, 0)) {
      cout << "impossible" << nl;
      return 0;
    }
  }

  for(int t=0; t<2; t++) {
    for(int i=0; i<n; i++) {
      if(ans[i] == t) {
        cout << names[i] << " ";
      }
    }
    cout << nl;
  }

  return 0;
}
