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


int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#ifdef USING_FAST_INPUT
  fast_input cin;
#endif

  const int B_filled = 10 * 17 - 12 * 2;
  const int P_filled = 10 * 10 + 3 * 4 - 12;

  int n, m;
  cin >> n >> m;
  vector g(n, vector<char>(m));
  int filled = 0;
  for(int i=0; i<n; i++) {
    for(int j=0; j<m; j++) {
      cin >> g[i][j];
      filled += (g[i][j] == '#');
    }
  }

  int holes = 0;
  for(int i=5; i<n; i++) {
    for(int j=5; j<m; j++) {
      bool ok = true;
      for(int di=0; di<=5; di++) {
        for(int dj=0; dj<=5; dj++) {
          if(di < 1 || di > 4 || dj < 1 || dj > 4) {
            ok &= (g[i-di][j-dj] == '#');
          } else if((di == 1 || di == 4) && (dj == 1 || dj == 4)) {
            ok &= (g[i-di][j-dj] == '#');
          } else {
            ok &= (g[i-di][j-dj] == '.');
          }
        }
      }
      holes += ok;
    }
  }

  // Bf * B + Pf * P = filled
  // 2 * B + P = holes
  // 2*Pf * B + Pf * P = holes * Pf
  // (2*Pf - Bf) * B = holes*Pf - filled
  int B = (holes * P_filled - filled) / (2 * P_filled - B_filled);
  int P = holes - 2 * B;
  cout << B << " " << P << nl;

  return 0;
}
