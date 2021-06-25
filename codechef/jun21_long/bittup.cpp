#include <bits/stdc++.h>
using namespace std;

#include "../../../lca/number/mod_int.h"

const char nl = '\n';
using ll = long long;

constexpr int MOD = 1e9 + 7;
using Int = mod_int<MOD>;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;
  while (T--) {
    int n, m;
    cin >> n >> m;
    cout << (Int(2).pow(n) - 1).pow(m) << nl;
  }

  return 0;
}