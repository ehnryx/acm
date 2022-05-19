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

  int n, m;
  cin >> n >> m;
  graph_list<void> graph(n+1);
  for(int i=0; i<m; i++) {
    int a, b;
    cin >> a >> b;
    graph.add_edge(a, b);
    graph.add_edge(b, a);
  }

  vector<int> ans(n+1);
  for(int i=1; i<=n; i++) {
    int mask = 0;
    for(int j : graph[i]) {
      mask |= 1 << ans[j];
    }
    if(mask == 0) {
      cout << "Impossible" << nl;
      return 0;
    }
    if(mask == 1) {
      ans[i] = 1;
    }
  }

  for(int i=1; i<=n; i++) {
    cout << (ans[i] ? "pub" : "house") << " ";
  }
  cout << nl;

  return 0;
}
