%:include <bits/stdc++.h>
using namespace std;

#include "../../../lca/misc/fast_input.h"

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
    int n, m, k;
    cin >> n >> m >> k;
    int least_h = (n % 2 == 0 ? 0 : m);
    int least_v = (m % 2 == 0 ? 0 : n);
    if(2*k < least_h || (n*m - 2*k) < least_v) {
      cout << "NO" << nl;
    } else if((least_h/2 - k) % 2 != 0) {
      cout << "NO" << nl;
    } else {
      cout << "YES" << nl;
    }
  }

  return 0;
}
