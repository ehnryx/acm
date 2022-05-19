#include <bits/stdc++.h>
using namespace std;

%:include "io/fast_input.h"

%:include "graph/graph_builder.h"
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

  auto g = *cin.getv<graph_builder<void>>();
  auto d = breadth_first(g, 1).get_dists();
  bool ok = true;
  for(int i=1; i<g.size(); i++) {
    if(d[i] == -1) {
      ok = false;
      cout << i << nl;
    }
  }
  if(ok) {
    cout << "Connected" << nl;
  }

  return 0;
}
