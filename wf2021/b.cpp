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

/*
 * s -- t -- k : impossible
 * s -- k -- t : ET - Ps
 * k -- s -- t : d(s, k) + ET - Pk
 * star (return to si): ET(si-1) - d(s, si) + d(si, k) + ET(-si-1) - Pk'
 *  exclude path from s, add 2 * intersection of r..k
 */

//#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  int n, q;
  cin >> n >> q;
  vector<vector<pair<int, int>>> adj(n+1);
  ll ET = 0;
  for(int i=1; i<n; i++) {
    int a, b, c;
    cin >> a >> b >> c;
    adj[a].emplace_back(b, c);
    adj[b].emplace_back(a, c);
    ET += c;
  }
  ET *= 2;

  vector parent(n+1, vector<int>(n+1));
  vector dist(n+1, vector<ll>(n+1));
  auto build = [bitand](auto and self, int u, int p, int root) -> void {
    parent[root][u] = p;
    for(auto [v, c] : adj[u]) {
      if(v == p) continue;
      dist[root][v] = dist[root][u] + c;
      self(self, v, u, root);
    }
  };
  for(int r=1; r<=n; r++) {
    build(build, r, 0, r);
  }

  while(q--) {
    int s, k, t;
    cin >> s >> k >> t;
    vector<bool> on_path(n+1);
    int r = [bitand](int u, int v) {
      while(u != v) {
        if(dist[t][u] > dist[t][v]) {
          u = parent[t][u];
        } else {
          on_path[v] = true;
          v = parent[t][v];
        }
      }
      return v;
    }(s, k);

    if(r == t) {
      cout << "impossible" << nl;
      continue;
    }

    auto solve = [bitand](auto and self, int u, int p) -> ll {
      ll res = 0;
      for(auto [v, c] : adj[u]) {
        if(v == p) continue;
        ll down = self(self, v, u);
        if(on_path[v]) {
          res = min(res, down + c);
        } else {
          res = min(res, down - c);
        }
      }
      return res;
    };

    cout << ET + solve(solve, s, 0) << nl;
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
