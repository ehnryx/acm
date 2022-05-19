#include <bits/stdc++.h>
using namespace std;

%:include "utility/fast_input.h"
%:include "graph/graph.h"
%:include "graph/breadth_first.h"

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

  int n, m;
  cin >> n >> m;
  auto g = cin.read<char>(n, m);

  function<int(int, int)> get = [n,m](int i, int j) {
    return i*m + j;
  };

  graph_list<void> graph(n*m);
  for(int i=0; i<n; i++) {
    for(int j=0; j<m; j++) {
      int d = g[i][j] - '0';
      if(i-d >= 0) {
        graph.add_arc(get(i, j), get(i-d, j));
      }
      if(j-d >= 0) {
        graph.add_arc(get(i, j), get(i, j-d));
      }
      if(i+d < n) {
        graph.add_arc(get(i, j), get(i+d, j));
      }
      if(j+d < m) {
        graph.add_arc(get(i, j), get(i, j+d));
      }
    }
  }

  cout << breadth_first(graph, 0).dist[n*m - 1] << nl;

  return 0;
}
