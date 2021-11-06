%:include <bits/stdc++.h>
using namespace std;

%:include "../../../lca/misc/fast_input.h"

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int INF = 0x3f3f3f3f;
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());


int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);

  fast_input cin;

  int T;
  cin >> T;
  while(T--) {
    int x, y, a, b;
    cin >> x >> y >> a >> b;
    // max u + v :
    //  au + bv <= x
    //  bu + av <= y
    // instead
    // max 2u + v :
    //  (a + b)u + av <= x
    //  (a + b)u + bv <= y
    //  --> (a - b)v <= x - y
    if(a == b) {
      cout << min(x, y) / a << nl;
    } else {
      if (a < b) swap(a, b);
      if (x < y) swap(x, y);
      int v = min((x - y) / (a - b), min(y / b, x / a));
      x -= v * a;
      y -= v * b;
      int u = min(x, y) / (a + b);
      x -= u * (a + b);
      y -= u * (a + b);
      int res = 2*u + v + (a <= x && b <= y);
      cout << res << nl;
    }
  }

  return 0;
}
