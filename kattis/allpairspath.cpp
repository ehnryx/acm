#include <bits/stdc++.h>
using namespace std;

%:include "utility/defines.h"
%:include "utility/fast_input.h"
%:include "utility/output.h"
%:include "graph/graph_edges.h"
%:include "graph/bellman_ford.h"
%:include "graph/graph.h"
%:include "graph/breadth_first.h"

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

  static constexpr int inf = 1e6;

  for(int n, m, q; cin >> n >> m >> q && n; ) {
    graph_edges<int> g(n);
    graph_list<void> rev(n);
    for(int i=0; i<m; i++) {
      int a, b, c;
      cin >> a >> b >> c;
      g.add_arc(a, b, c);
      rev.add_arc(b, a);
    }

    vector<vector<int>> dists;
    vector<vector<bool>> negs;
    vector<vector<int>> revds;
    for(int i=0; i<n; i++) {
      bellman_ford bf(g, i, inf);
      dists.push_back(bf.get_dists());
      negs.push_back(bf.get_negatives());
      revds.push_back(breadth_first(rev, i).get_dists());
    }

    while(q--) {
      int s, t;
      cin >> s >> t;
      if(dists[s][t] == inf) {
        cout << "Impossible" << nl;
      } else {
        bool neg = false;
        for(int i=0; !neg && i<n; i++) {
          neg |= (dists[s][i] != inf && negs[s][i] && rev[t][i] != -1);
        }
        if (neg) {
          cout << "-Infinity" << nl;
        } else {
          cout << dists[s][t] << nl;
        }
      }
    }
    cout << nl;
  }

  return 0;
}
