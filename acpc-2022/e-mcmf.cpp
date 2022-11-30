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

  // not sparse
  min_cost_flow<int, int, false> g(n + 1);
  for(int i=0; i<m; i++) {
    int a, b;
    cin >> a >> b;
    g.add_edge(a, b, 1, -1);
    g.add_edge(a, b, m-1, 0);
  }

  int l = 1;
  int r = m;
  while(l < r) {
    int guess = (l + r) / 2;
    g.clear_flow();
    g.add_edge(n-1, n, guess, 0);
    auto [flow, cost] = g.flow(0, n);
    g.adj[n-1].pop_back();
    g.adj[n].pop_back();
    if(cost == -m) {
      r = guess;
    } else {
      l = guess + 1;
    }
  }

  cout << r << nl;
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
