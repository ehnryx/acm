#include <bits/stdc++.h>
using namespace std;

%:include "utility/fast_input.h"
%:include "graph/graph.h"
%:include "graph/dijkstra.h"
%:include "graph/biconnected_components.h"

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
  graph_list<ll> g(n), rg(n);
  for(int i=0; i<m; i++) {
    int a, b, c;
    cin >> a >> b >> c;
    g.add_arc(a, b, c);
    rg.add_arc(b, a, c);
  }
  int s, t;
  cin >> s >> t;

  auto dist = dijkstra(g, s, -1).get_dists();
  auto rdist = dijkstra(rg, t, -1).get_dists();

  graph_list<void> bg(n);
  for(int i=0; i<n; i++) {
    if(dist[i] == -1 || rdist[i] == -1) continue;
    if(dist[i] + rdist[i] != dist[t]) continue;
    for(auto [v, c] : g[i]) {
      if(dist[v] + rdist[v] == dist[t]) {
        bg.add_edge(i, v);
      }
    }
  }
  biconnected_components bcc(bg);

  for(int i=0; i<n; i++) {
    if(i == s || i == t || bcc.is_cut_vertex(i)) {
      cout << i << " ";
    }
  }
  cout << nl;

  return 0;
}
