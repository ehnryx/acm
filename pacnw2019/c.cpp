#include <bits/stdc++.h>
using namespace std;

#include "../../lca/graph/graph.h"
//#include "../../lca/graph/breadth_first.h"
#include "../../lca/graph/dijkstra.h"

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

  //graph_list<void> graph(n + 1);
  graph_list<int> graph(n + 1);
  for(int i=0; i<m; i++) {
    int a, b;
    cin >> a >> b;
    //graph.add_edge(a, b);
    //graph.add_edge(b, a);
    graph.add_edge(a, b, 1);
    graph.add_edge(b, a, 1);
  }

  //breadth_first bfs(graph, 1);
  dijkstra bfs(graph, 1, -1);
  cout << bfs.get_dists()[n] - 1 << nl;

  return 0;
}
