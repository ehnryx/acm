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
  int n;
  cin >> n;
  vector cost(2*n, vector<int>(2*n));
  for(int i=0; i<2*n; i++) {
    for(int j=0; j<2*n; j++) {
      cin >> cost[i][j];
    }
  }

  struct output {
    int cost;
    vector<tuple<int, int, int, int>> solution;
    bool operator<(const output& o) const {
      return cost < o.cost;
    }
  };
  output ans{ numeric_limits<int>::max(), {} };

  for(int s=0; s<=n; s++) {
    min_cost_flow<int, int> g(4*n + 2);
    const int source = 4*n;
    const int sink = 4*n + 1;
    for(int i=0; i<n; i++) {
      g.add_edge(source, i, 1, 0);
      g.add_edge(n + i, sink, 1, 0);
      for(int j=0; j<n; j++) {
        g.add_edge(i, 2*n + j, 1, cost[i][2*j + (j>=s)]);
      }
      for(int j=0; j<n; j++) {
        g.add_edge(3*n + j, n + i, 1, cost[n+i][2*j + (j>=s)]);
      }
      g.add_edge(2*n + i, 3*n + i, 1, 0);
    }
    auto [_, cur] = g.flow(source, sink);

    vector<tuple<int, int, int, int>> res;
    for(int i=0; i<n; i++) {
      int l = -1, r = -1;
      for(const auto& e : g.adj[2*n + i]) {
        if(e.flow < 0) {
          l = e.to;
        }
      }
      for(const auto& e : g.adj[3*n + i]) {
        if(e.flow > 0) {
          r = e.to;
        }
      }
      assert(l != -1 and r != -1);
      res.emplace_back(l % n + 1, i + 1, (i < s ? 'A' : 'B'), r % n + 1);
    }
    sort(begin(res), end(res));

    ans = min(ans, output{ cur, res });
  }

  cout << ans.cost << nl;
  for(auto [a, b, t, c] : ans.solution) {
    cout << a << " " << b << (char)t << " " << c << nl;
  }
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
