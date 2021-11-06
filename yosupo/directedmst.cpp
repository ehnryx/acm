#include <bits/stdc++.h>
using namespace std;

#include "../../lca/graph/min_arborescence.h"

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int INF = 0x3f3f3f3f;
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());


int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);

  int n, m, s;
  cin >> n >> m >> s;
  min_arborescence<ll> arb(n);
  for(int i=0; i<m; i++) {
    int a, b, c;
    cin >> a >> b >> c;
    arb.add_edge(a, b, c);
  }
  arb.build();
  auto [in, ans] = arb.solve(s);
  cout << ans << nl;
  for(int i=0; i<n; i++) {
    if(i == s) cout << i << " ";
    else cout << in[i].first << " ";
  }
  cout << nl;

  return 0;
}
