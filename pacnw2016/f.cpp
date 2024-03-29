#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
//%:include "utility/output.h"

%:include "graph/two_sat.h"

using ll = long long;
using ld = long double;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());


//#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  int n, r, l;
  cin >> n >> r >> l;
  vector g(n+1, vector(n+1, -1));
  for(int i=0; i<l; i++) {
    int ri, ci;
    cin >> ri >> ci;
    g[ri][ci] = i;
  }
  two_sat sat(l);
  for(int i=1; i<=n; i++) {
    for(int j=1; j<=n; j++) {
      if(g[i][j] == -1) continue;
      for(int k=1; k<=2*r; k++) {
        if(i+k <= n and g[i+k][j] != -1) {
          sat.or_clause(g[i][j], true, g[i+k][j], true);
        }
        if(j+k <= n and g[i][j+k] != -1) {
          sat.or_clause(g[i][j], false, g[i][j+k], false);
        }
      }
    }
  }
  if(sat.solve()) {
    cout << "YES" << nl;
  } else {
    cout << "NO" << nl;
  }
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
