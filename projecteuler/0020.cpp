#pragma GCC optimize("O3")

#include <bits/stdc++.h>
using namespace std;

#include "../../lca/number/int_base10.h"

constexpr char nl = '\n';
using ll = long long;

using Int = int_base10;

int main(int argc, char** argv) {
  cin.tie(0)->sync_with_stdio(0);

  ll n = 100;
  if (argc > 1) n = atoll(argv[1]);

  Int f = 1;
  for(int i=1; i<=n; i++) {
    f *= i;
  }

  Int ans = 0;
  while(f > 0) {
    ans += f % 10;
    f /= 10;
  }
  cout << ans << nl;

  return 0;
}
