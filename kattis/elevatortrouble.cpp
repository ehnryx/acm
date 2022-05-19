#include <bits/stdc++.h>
using namespace std;

%:include "io/fast_input.h"

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

  int f, s, t, u, d;
  cin >> f >> s >> t >> u >> d;
  graph_list<void> g(f+1, true);
  for(int i=1; i<=f; i++) {
    if(i+u <= f) {
      g.add_edge(i, i+u);
    }
    if(i-d > 0) {
      g.add_edge(i, i-d);
    }
  }

  int ans = breadth_first(g, s).get_dists()[t];
  if(ans == -1) {
    cout << "use the stairs" << nl;
  } else {
    cout << ans << nl;
  }

  return 0;
}
