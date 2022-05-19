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

  int n;
  cin >> n;
  graph_list<void> g(n+1);
  vector<pair<int, int>> edges;
  for(int i=1; i<n; i++) {
    int a, b;
    cin >> a >> b;
    g.add_edge(a, b);
    edges.emplace_back(a, b);
  }

  auto dist = breadth_first(g, 1).get_dists();
  for(auto [a, b] : edges) {
    if(min(dist[a], dist[b]) % 2) {
      cout << (dist[a] < dist[b]) << nl;
    } else {
      cout << (dist[a] > dist[b]) << nl;
    }
  }

  return 0;
}
