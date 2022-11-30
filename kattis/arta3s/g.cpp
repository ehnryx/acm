#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
//%:include "utility/output.h"

// TODO upgrade dfs to support cycle detection
%:include "graph/strongly_connected.h"

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
  vector<vector<int>> g(n);
  vector<pair<int, int>> bad;
  for(int i=0; i<m; i++) {
    int a, b;
    char op;
    cin >> a >> op >> b;
    if(op == '<') {
      g[a].push_back(b);
      bad.emplace_back(a, b);
    } else if(op == '>') {
      g[b].push_back(a);
      bad.emplace_back(a, b);
    } else {
      g[a].push_back(b);
      g[b].push_back(a);
    }
  }
  strongly_connected scc(g);
  for(auto [a, b] : bad) {
    if(scc[a] == scc[b]) {
      return void(cout << "inconsistent" << nl);
    }
  }
  cout << "consistent" << nl;
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
