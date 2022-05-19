#include <bits/stdc++.h>
using namespace std;

%:include "io/fast_input.h"
%:include "data_structure/prefix_sum.h"

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());


int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#ifdef USING_FAST_INPUT
  fast_input cin;
#endif

  int n, m;
  cin >> n >> m;
  vector g(n, vector<int>(n));
  for(auto [a, b] : cin.read<pair<int, int>>(m)) {
    g[a-1][b-1] = 1;
  }
  prefix_sum<int, 2> sum(g);

  int ans = m;

  for(int i=1; i<=m; i++) {
    if(m % i) continue;
    int j = m / i;
    if(max(i, j) > n) continue;

    for(int si=0; si+i<=n; si++) {
      for(int sj=0; sj+j<=n; sj++) {
        int have = sum.query(si, sj, si+i-1, sj+j-1);
        ans = min(ans, m - have);
      }
    }
  }

  cout << ans << nl;

  return 0;
}
