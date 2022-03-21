#include <bits/stdc++.h>
using namespace std;

#include "../../../lca/graph/graph.h"
#include "../../../lca/graph/dijkstra.h"

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

  graph_list<ll> g(n + 1);

  for(int i=0; i<m; i++) {
    int a, b, c;
    cin >> a >> b >> c;
    g.add_edge(a, b, c);
    g.add_edge(b, a, c);
  }

  dijkstra bfs(g, 1, -1);
  if(bfs.get_dists()[n] == -1) {
    cout << -1 << nl;
  } else {
    for (int v : bfs.get_path(n)) {
      cout << v << " ";
    }
    cout << nl;
  }

  return 0;
}
