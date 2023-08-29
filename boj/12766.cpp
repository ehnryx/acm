#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
//%:include "utility/output.h"

%:include "graph/dijkstra.h"
%:include "utility/nd_array.h"

using ll = long long;
using ld = long double;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());


//#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  int n, k, s, m;
  cin >> n >> k >> s >> m;
  graph_t<int> graph(n+1), rev(n+1);
  for(int i=0; i<m; i++) {
    int a, b, c;
    cin >> a >> b >> c;
    graph.add_arc(a, b, c);
    rev.add_arc(b, a, c);
  }
  auto dijk1 = dijkstra(graph, numeric_limits<int>::max()).run(k+1);
  auto dijk2 = dijkstra(rev, numeric_limits<int>::max()).run(k+1);

  vector<int> a(k+1);
  for(int i=1; i<=k; i++) {
    a[i] = dijk1.dist[i] + dijk2.dist[i];
  }
  sort(begin(a) + 1, end(a));
  partial_sum(begin(a), end(a), begin(a));

  nd_array<ll, 2> dp(s, k+1, numeric_limits<ll>::max() / 2);
  for(int i=1; i<=k; i++) {
    dp(0, i) = (a[i] - a[0]) * (ll)(i - 1);
  }

  auto solve = [&](auto&& self, int t, int l, int r, int optl, int optr) -> void {
    if(l > r) return;
    int mid = (l + r) / 2;
    int opt = -1;
    for(int j = optl; j <= min(mid-1, optr); j++) {
      ll cur = (ll)(a[mid] - a[j]) * (mid - j - 1) + dp(t-1, j);
      if(cur < dp(t, mid)) {
        dp(t, mid) = cur;
        opt = j;
      }
    }
    self(self, t, l, mid-1, optl, opt);
    self(self, t, mid+1, r, opt, optr);
  };

  for(int t=1; t<s; t++) {
    solve(solve, t, t+1, k, t, k-1);
  }

  cout << dp(s-1, k) << nl;
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
