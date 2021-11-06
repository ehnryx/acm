#include <bits/stdc++.h>
using namespace std;

#include "../../../lca/misc/fast_input.h"
//#include "../../../lca/data_structure/splay_tree.h"

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
    ll x, y;
    cin >> x >> y;
    if(x < y) {
      cout << y - (y%x)/2 << nl;
    } else if(x == y) {
      cout << x << nl;
    } else {
      cout << x + y << nl;
    }
  }

  return 0;
}
