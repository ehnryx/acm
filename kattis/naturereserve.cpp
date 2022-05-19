#include <bits/stdc++.h>
using namespace std;

%:include "utility/fast_input.h"
%:include "graph/edge_list.h"
%:include "graph/min_span_forest.h"

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

  int T;
  cin >> T;
  while(T--) {
    int n, m, k, s;
    cin >> n >> m >> k >> s;
    vector<pair<int, int>> init;
    for(int i=0; i<s; i++) {
      int v;
      cin >> v;
      init.emplace_back(0, v);
    }
    graph_edges<ll> graph(n+1);
    for(int i=0; i<m; i++) {
      int a, b, c;
      cin >> a >> b >> c;
      graph.add_arc(a, b, c);
    }
    ll ans = min_span_forest(graph, init).get_weight();
    cout << ans + (n - s) * (ll)k << nl;
  }

  return 0;
}
