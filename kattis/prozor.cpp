#include <bits/stdc++.h>
using namespace std;

%:include "utility/fast_input.h"
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

  int n, m, k;
  cin >> n >> m >> k;
  auto out = cin.read<char>(n, m);
  vector g(n, vector<int>(m));
  for(int i=0; i<n; i++) {
    for(int j=0; j<m; j++) {
      g[i][j] = (out[i][j] == '*');
    }
  }

  prefix_sum<int, 2> s(g);
  tuple<int, int, int> best(-1, 0, 0);
  for(int i=0; i+k<=n; i++) {
    for(int j=0; j+k<=m; j++) {
      best = max(best, tuple(s.query(i+1, j+1, i+k-2, j+k-2), i, j));
    }
  }

  {
    auto [ans, i, j] = best;
    cout << ans << nl;
    for(int t=0; t<k; t++) {
      out[i][j+t] = '-';
      out[i+k-1][j+t] = '-';
      out[i+t][j] = '|';
      out[i+t][j+k-1] = '|';
    }
    out[i][j] = out[i+k-1][j] = out[i][j+k-1] = out[i+k-1][j+k-1] = '+';
  }

  for(int i=0; i<n; i++) {
    for(int j=0; j<m; j++) {
      cout << out[i][j];
    }
    cout << nl;
  }

  return 0;
}
