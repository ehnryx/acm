#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
%:include "utility/output.h"

%:include "ds/dynamic_hull.h"
%:include "graph/dijkstra.h"

using ll = long long;
using ld = long double;

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

  int n, m, k;
  cin >> n >> m >> k;
  graph_list<ll> graph(n+1);
  for(int i=0; i<m; i++) {
    int a, b, c;
    cin >> a >> b >> c;
    graph.add_edge(a, b, c);
  }

  struct Item {
    int u;
    ll d;
    bool operator < (const Item& o) const {
      return d > o.d;
    }
  };
  dijkstra dijk(graph, 1, -1);
  const vector<ll>& dist = dijk.get_dists();

  while(k--) {
    dynamic_hull_min<ll> hull;
    for(int i=1; i<=n; i++) {
      if(dist[i] == -1) continue;
      hull.insert(-2*i, dist[i] + (ll)i*i);
    }
    vector<decltype(dijk)::Item> sources;
    for(int i=1; i<=n; i++) {
      ll f = hull.query(i) + (ll)i*i;
      if(dist[i] != -1) f = min(f, dist[i]);
      sources.emplace_back(i, f);
    }
    dijk.run(graph, sources); // updates dist because reference
  }

  cout << subvector(dist, 1, n) << nl;

  return 0;
}
