#include <bits/stdc++.h>
using namespace std;

// #include "../../lca/data_structure/splay_tree.h" ... sad
#include "../../lca/number/mod_int.h"

const char nl = '\n';
const int MOD = 1e9+7;

using Int = mod_int<MOD>;

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  int n, k;
  cin >> n >> k;
  if (n == 1) {
    cout << 1 << nl;
    return 0;
  }

  Int ans = 1;
  int e = (n-1)/(k+1);
  ans += Int(2) * Int(k+1) * (Int(2).pow(e) - Int(1));
  Int extra = (n-1)%(k+1);
  ans += Int(2) * extra * Int(2).pow(e);

  cout << ans << nl;

  return 0;
}
