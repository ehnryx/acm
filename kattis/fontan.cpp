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

  fast_input cin;

  int n, m;
  cin >> n >> m;
  auto g = cin.read<char, 1, 1>(n, m);
  for(int i=1; i<=n; i++) {
    for(int j=1; j<=m; j++) {
      if(g[i][j] == 'V' && g[i+1][j] == '#' && g[i][j+1] == '.') {
        g[i][j+1] = 'V';
      }
    }
    for(int j=m; j>=1; j--) {
      if(g[i][j] == 'V' && g[i+1][j] == '#' && g[i][j-1] == '.') {
        g[i][j-1] = 'V';
      }
    }
    for(int j=1; j<=m; j++) {
      if(g[i][j] == 'V' && g[i+1][j] == '.') {
        g[i+1][j] = 'V';
      }
    }
  }

  for(int i=1; i<=n; i++) {
    for(int j=1; j<=m; j++) {
      cout << g[i][j];
    }
    cout << nl;
  }

  return 0;
}
