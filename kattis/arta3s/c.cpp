#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
//%:include "utility/output.h"

%:include "graph/depth_first.h"

using ll = long long;
using ld = long double;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());


//#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  int n, m;
  cin >> n >> m;
  vector<int> a(n);
  for(int i=0; i<n; i++) {
    cin >> a[i];
  }
  vector_graph<void> g(n);
  for(int i=0; i<m; i++) {
    int u, v;
    cin >> u >> v;
    g.add_edge(u, v);
  }
  depth_first dfs(g);
  for(int i=0; i<n; i++) {
    if(not dfs.visited(i)) {
      int value = 0;
      dfs.run_node_func(i, [&](int u) { value += a[u]; });
      if(value != 0) {
        return void(cout << "IMPOSSIBLE" << nl);
      }
    }
  }
  cout << "POSSIBLE" << nl;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#ifdef USING_FAST_INPUT
  fast_input cin;
#endif

  int T = 1;
#ifdef MULTI_TEST
  cin >> T;
#endif
  for(int testnum=1; testnum<=T; testnum++) {
    solve_main(testnum, cin);
  }

  return 0;
}
