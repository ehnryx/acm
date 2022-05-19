#include <bits/stdc++.h>
using namespace std;

%:include "io/fast_input.h"

%:include "graph/graph_builder.h"
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

  auto graph = *cin.getv<graph_builder<uint64_t>>();
  auto verts = cin.read<int>(7);
  verts.push_back(1);
  sort(begin(verts), end(verts));
  verts.resize(unique(begin(verts), end(verts)) - begin(verts));

  map<int, dijkstra<decltype(graph)>> dijks;
  for(int v : verts) {
    dijks.try_emplace(v, graph, v, -1);
  }

  uint64_t ans = -1;
  do {
    uint64_t cur = 0;
    for(int i=1; i<size(verts); i++) {
      cur += dijks.at(verts[i]).dist[verts[i-1]];
    }
    ans = min(ans, cur);
  } while(next_permutation(begin(verts) + 1, end(verts)));

  if(ans < 1ull << 63) {
    cout << ans << nl;
  } else {
    cout << -1 << nl;
  }

  return 0;
}
