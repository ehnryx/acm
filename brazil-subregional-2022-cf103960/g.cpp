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

struct segment {
  int a, b, c, d;
  segment(int a_, int b_, int c_, int d_): a(a_), b(b_), c(c_), d(d_) {
    if(tie(a, b) > tie(c, d)) {
      swap(a, c);
      swap(b, d);
    }
    assert(tie(a, b) <= tie(c, d));
  }
  bool operator < (const segment& o) const {
    return tie(a, b, c, d) < tie(o.a, o.b, o.c, o.d);
  }
};

//#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  int n;
  cin >> n;
  map<segment, vector<int>> edges;
  vector<ll> area(n);
  for(int i=0; i<n; i++) {
    ll a, b, c, d, e, f;
    cin >> a >> b >> c >> d >> e >> f;
    edges[segment(a, b, c, d)].push_back(i);
    edges[segment(c, d, e, f)].push_back(i);
    edges[segment(e, f, a, b)].push_back(i);
    area[i] = abs(a * d + c * f + e * b - b * c - d * e - f * a);
  }

  vector<vector<int>> adj(n);
  for(const auto& [_, v] : edges) {
    assert(size(v) <= 2);
    if(size(v) == 2) {
      adj[v[0]].push_back(v[1]);
      adj[v[1]].push_back(v[0]);
    }
  }

  vector dp(n, vector<ll>(2, -1));
  auto solve = [&](auto self, int u, int p, bool must) -> ll {
    if(dp[u][must] != -1) return dp[u][must];
    if(auto it = find(begin(adj[u]), end(adj[u]), p); it != end(adj[u])) {
      adj[u].erase(it);
    }
    // take
    ll res = area[u];
    for(int v : adj[u]) {
      res += self(self, v, u, false);
    }
    // skip
    if(!must and size(adj[u]) == 2) {
      ll skip = 0;
      for(int v : adj[u]) {
        skip += self(self, v, u, true);
      }
      res = min(res, skip);
    }
    return dp[u][must] = res;
  };

  int root = 0;
  for(int i=0; i<n; i++) {
    if(size(adj[i]) != 3) {
      root = i;
      break;
    }
  }
  ll ans = solve(solve, root, -1, true);

  cout << ans / 2.0 << nl;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(1);
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
