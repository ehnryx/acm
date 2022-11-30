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


//#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  int n, m, k;
  cin >> n >> m >> k;
  int area = n*m / k;
  if(area * k != n*m) {
    return void(cout << "IMPOSSIBLE" << nl);
  }

  int a = gcd(n, k);
  int b = gcd(m, k / a);
  a = n/a;
  b = m/b;
  vector g(n, string(m, 0));
  for(int si=0, out='A'; si<n; si+=a) {
    for(int sj=0; sj<m; sj+=b, out++) {
      for(int i=0; i<a; i++) {
        for(int j=0; j<b; j++) {
          g[si + i][sj + j] = out;
        }
      }
    }
  }

  for(int i=0; i<n; i++) {
    cout << g[i] << nl;
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
