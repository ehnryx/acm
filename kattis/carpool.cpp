#include <bits/stdc++.h>
using namespace std;

//%:include "io/fast_input.h"
%:include "graph/floyd_warshall.h"

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
  floyd_warshall<unsigned> trivial(n + 2, -1);
  for(int i=0; i<m; i++) {
    int a, b, c;
    cin >> a >> b >> c;
    trivial.add_edge(a, b, c);
  }
  trivial.run();

  vector<unsigned> cost(1 << n, -1);
  for(int bm=1; bm<1<<n; bm++) {
    if(__builtin_popcount(bm) > 5) continue;
    vector<int> have;
    for(int i=0; i<n; i++) {
      if(bm & 1<<i) {
        have.push_back(i + 1);
      }
    }
    do {
      unsigned cur = 0;
      int at = 0;
      for(int i : have) {
        cur += trivial[at][i];
        at = i;
      }
      cur += trivial[at][n + 1];
      cost[bm] = min(cost[bm], cur);
    } while (next_permutation(begin(have), end(have)));
    cost[bm] += __builtin_popcount(bm) * 5;
  }

  vector dp(4, vector<unsigned>(1 << n, -1));
  dp[0][0] = 0;
  for(int i=1; i<=3; i++) {
    for(int bm=1; bm<1<<n; bm++) {
      for(int sm=bm; sm; sm=(sm-1)&bm) {
        if(__builtin_popcount(sm) > 5) continue;
        dp[i][bm] = min(dp[i][bm], max(dp[i-1][bm ^ sm], cost[sm]));
      }
    }
  }

  unsigned ans = -1;
  for(int i=1; i<=3 && ans == -1; i++) {
    ans = min(ans, dp[i][(1 << n) - 1]);
  }
  cout << ans << nl;

  return 0;
}
