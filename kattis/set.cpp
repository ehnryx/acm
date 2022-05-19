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

  auto g = cin.read<string>(12);
  vector<tuple<int, int, int>> ans;
  for(int i=0; i<12; i++) {
    for(int j=0; j<i; j++) {
      for(int k=0; k<j; k++) {
        bool ok = true;
        for(int t=0; t<4; t++) {
          ok &= (g[i][t] == g[j][t] && g[j][t] == g[k][t]) ||
            (g[i][t] != g[j][t] && g[j][t] != g[k][t] && g[k][t] != g[i][t]);
        }
        if(ok) {
          ans.emplace_back(k, j, i);
        }
      }
    }
  }

  if(empty(ans)) {
    cout << "no sets" << nl;
  } else {
    sort(begin(ans), end(ans));
    for(auto [a, b, c] : ans) {
      cout << a + 1 << " " << b + 1 << " " << c + 1 << nl;
    }
  }

  return 0;
}
