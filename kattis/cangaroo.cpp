#include <bits/stdc++.h>
using namespace std;

%:include "io/fast_input.h"

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
  auto g = cin.read<char>(n, m);
  reverse(begin(g), end(g));

  vector dp(n+1, vector<unsigned>(1<<m, -1));
  int start = 0;
  for(int i=1; i<m; i+=2) {
    start |= 1 << i;
  }
  dp[0][start] = 0;

  vector<int> valid;
  for(int bm=0; bm<1<<m; bm++) {
    if((bm & (bm << 1)) || (bm & 1)) continue;
    valid.push_back(bm);
  }

  for(int i=0; i<n; i++) {
    for(int bm : valid) {
      bool bad = false;
      for(int j=0; j<m; j++) {
        if(g[i][j] == '#' && !(bm & 3<<j)) {
          bad = true;
          break;
        }
      }
      if(bad) continue;

      if(i % 2) {
        dp[i+1][bm] = dp[i][bm];
      } else {
        for(int om : valid) {
          if(dp[i][om] == -1) continue;
          bool ok = true;
          for(int j=0; j<m; j++) {
            if(bm & 1<<j) {
              ok &= (om & 1 << j) || (om & 1 << (j-1)) || (om & 1 << (j+1));
            }
          }
          if(ok) {
            dp[i+1][bm] = min(dp[i+1][bm], dp[i][om] + __builtin_popcount(bm));
          }
        }
      }
    }
  }

  cout << *min_element(begin(dp[n]), end(dp[n])) << nl;

  return 0;
}
