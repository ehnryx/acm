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


//#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  int n, m;
  cin >> n >> m;
  vector<int> a(n);
  vector<ll> adj(m);
  for(int i=0; i<n; i++) {
    cin >> a[i];
    a[i] -= 1;
    if(i) {
      adj[min(a[i], a[i-1])] |= 1ll << max(a[i], a[i-1]);
    }
  }
  adj[a.front()] |= 1ll << a.front();
  adj[a.back()] |= 1ll << a.back();
  vector<int> cost(m);
  for(int i=0; i<m; i++) {
    cin >> cost[i];
  }

  // max independent set
  auto solve = [&](auto&& self, ll bm) -> int {
    if(bm == 0) return 0;
    int u = __builtin_ctzll(bm);
    if(adj[u] & 1ll << u) {
      return self(self, bm ^ 1ll << u);
    }

    int nbs = 0;
    ll nxt = bm ^ 1ll << u;
    for(int i=u+1; i<m; i++) {
      if(nxt & adj[u] & 1ll << i) {
        nxt ^= 1ll << i;
        nbs++;
      }
    }

    if(nbs == 0) {
      return cost[u] + self(self, nxt);
    }
    return max(cost[u] + self(self, nxt), self(self, bm ^ 1ll << u));
  };

  cout << accumulate(begin(cost), end(cost), 0) - solve(solve, (1ll << m) - 1) << nl;
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
