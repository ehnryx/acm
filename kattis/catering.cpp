#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
//%:include "utility/output.h"

%:include "graph/min_cost_flow.h"

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
  min_cost_flow<int, int> g(2 * (n+1) + 2);
  for(int i=0; i<n; i++) {
    for(int j=i+1; j<=n; j++) {
      int cost;
      cin >> cost;
      g.add_edge(i, n+1 + j, 1, cost);
    }
  }
  const int source = 2 * (n+1);
  const int sink = source + 1;
  g.add_edge(source, 0, m, 0);
  for(int i=1; i<=n; i++) {
    g.add_edge(source, i, 1, 0);
    g.add_edge(n+1 + i, sink, 1, 0);
  }

  auto [flow, cost] = g.flow(source, sink);
  assert(flow == n);
  cout << cost << nl;
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
