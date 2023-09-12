#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
//%:include "utility/output.h"

using ll = long long;
using ld = long double;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

struct edge {
  int to, h, i;
};

//#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  int n;
  cin >> n;
  vector<vector<edge>> adj(n+1);
  for(int i=0; i<n; i++) {
    int a, b, h;
    cin >> a >> b >> h;
    adj[a].emplace_back(b, h, i);
    adj[b].emplace_back(a, h, i);
  }

  vector<bool> vis(n+1);
  vector<edge> eval(n);
  auto build = [&](auto&& self, vector<pair<int, int>>& cyc, int u, int p) -> int {
    vis[u] = true;
    for(auto [v, h, i] : adj[u]) {
      if(v == p) continue;
      if(not vis[v]) {
        int to = self(self, cyc, v, u);
        if(to != -1) {
          cyc.emplace_back(u, i);
          eval[i] = { v, h, i };
          return to == u ? -1 : to;
        }
      } else {
        cyc.emplace_back(u, i);
        eval[i] = { v, h, i };
        return v;
      }
    }
    return -1;
  };
  vector<pair<int, int>> cycle;
  build(build, cycle, 1, 0);

  vector<bool> in_cycle(n);
  for(auto [u, i] : cycle) {
    in_cycle[i] = true;
  }

  vector<int> ans(n);
  vector<unordered_set<int>> seen(n+1);
  auto orient = [&](auto&& self, int u, int p) -> bool {
    for(auto [v, h, i] : adj[u]) {
      if(v == p or in_cycle[i]) continue;
      if(not self(self, v, u)) {
        return false;
      }
      if(not seen[u].insert(h).second) {
        return false;
      }
      ans[i] = v;
    }
    return true;
  };

  for(auto [u, i] : cycle) {
    if(not orient(orient, u, 0)) {
      return void(cout << "impossible" << nl);
    }
  }

  bool up = true;
  bool down = true;
  for(auto [u, i] : cycle) {
    up &= not seen[u].count(eval[i].h);
    down &= not seen[eval[i].to].count(eval[i].h);
  }

  if(up) {
    for(auto [u, i] : cycle) {
      ans[i] = eval[i].to;
    }
  } else if(down) {
    for(auto [u, i] : cycle) {
      ans[i] = u;
    }
  } else {
    return void(cout << "impossible" << nl);
  }

  for(int v : ans) {
    cout << v << " ";
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
