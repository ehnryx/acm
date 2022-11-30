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
  int n, boats, m;
  cin >> n >> boats >> m;
  vector<bool> have(n+1);
  for(int i=0; i<boats; i++) {
    int v;
    cin >> v;
    have[v] = true;
  }
  vector_graph<void> g(n+1);
  for(int i=0; i<m; i++) {
    int a, b;
    cin >> a >> b;
    g.add_edge(a, b);
  }
  depth_first dfs(g);
  int ans = 0;
  for(int i=1; i<=n; i++) {
    if(dfs.visited(i)) continue;
    int cnt = 0;
    dfs.run_node_func(i, [&](int u) { cnt += have[u]; });
    ans += cnt == 0;
  }
  cout << ans << nl;
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
