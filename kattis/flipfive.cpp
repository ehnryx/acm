#include <bits/stdc++.h>
using namespace std;

%:include "utility/fast_input.h"

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

  int T;
  cin >> T;
  while(T--) {
    auto g = cin.read<char>(3, 3);
    int ans = 9;
    for(int bm=0; bm<1<<9; bm++) {
      bool ok = true;
      for(int i=0; i<3; i++) {
        for(int j=0; j<3; j++) {
          int f = bm >> (i*3 + j) & 1;
          if(i) f ^= bm >> ((i-1)*3 + j) & 1;
          if(j) f ^= bm >> (i*3 + (j-1)) & 1;
          if(i+1 < 3) f ^= bm >> ((i+1)*3 + j) & 1;
          if(j+1 < 3) f ^= bm >> (i*3 + (j+1)) & 1;
          ok &= (f == (g[i][j] == '*'));
        }
      }
      if(ok) {
        ans = min(ans, __builtin_popcount(bm));
      }
    }
    cout << ans << nl;
  }

  return 0;
}
