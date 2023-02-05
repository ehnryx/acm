#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
//%:include "utility/output.h"

%:include "number/mod_int.h"

using ll = long long;
using ld = long double;

constexpr char nl = '\n';
constexpr int MOD = 1e9 + 7;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

using Int = mod_int<MOD>;

//#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  int n;
  cin >> n;
  vector<int> to(n+1);
  for(int i=1; i<=n; i++) {
    cin >> to[i];
  }

  vector<int> remap(n+1);
  vector<bool> root(n+1);
  for(int i=1; i<=n; i++) {
    if(remap[i]) continue;
    int u = i;
    vector<int> path;
    while(not remap[u]) {
      remap[u] = -1;
      path.push_back(u);
      u = to[u];
    }
    if(remap[u] == -1) {
      root[u] = true;
      remap[u] = u;
      while(not empty(path) and path.back() != u) {
        remap[path.back()] = u;
        path.pop_back();
      }
      path.pop_back();
    }
    for(int v : path) {
      remap[v] = v;
    }
  }

  vector<vector<int>> adj(n+1);
  for(int i=1; i<=n; i++) {
    if(remap[i] == remap[to[i]]) continue;
    adj[remap[to[i]]].push_back(remap[i]);
  }

  auto solve = [&](auto&& self, int u) -> Int {
    Int res = 1;
    for(int v : adj[u]) {
      res *= self(self, v);
    }
    return res + 1;
  };

  Int ans = 1;
  for(int i=1; i<=n; i++) {
    if(root[i]) {
      ans *= solve(solve, i);
    }
  }
  cout << ans - 1 << nl;
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
