#include <bits/stdc++.h>
using namespace std;

%:include "io/fast_input.h"
%:include "graph/graph.h"
%:include "graph/dijkstra.h"

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
#ifdef USING_FAST_INPUT
  fast_input cin;
#endif

  int n;
  cin >> n;
  auto cost = cin.read<int>(n);
  graph_list<int> graph(n*n, true);
  for(int i=0; i<n; i++) {
    for(int j=0; j+1<n; j++) {
      int u = i + j*n;
      if(int ni = i + j + 1; ni < n) {
        int v = ni + (j+1)*n;
        graph.add_edge(u, v, cost[ni]);
      }
      if(int pi = i - j; pi >= 0) {
        int v = pi + j*n;
        graph.add_edge(u, v, cost[pi]);
      }
    }
  }

  int ans = numeric_limits<int>::max();
  auto dist = dijkstra(graph, 0, ans).get_dists();
  for(int j=0; j<n; j++) {
    ans = min(ans, dist[n-1 + j*n]);
  }
  cout << ans << nl;

  return 0;
}
