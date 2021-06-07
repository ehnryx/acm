#pragma GCC optimize("O3")

#include <bits/stdc++.h>
using namespace std;

#include "../../lca/number/int_base10.h"

constexpr char nl = '\n';
using ll = long long;
using Int = int_base10;

int main(int argc, char** argv) {
  cin.tie(0)->sync_with_stdio(0);

  ll n = 10'000'000;
  if (argc > 1) n = atoll(argv[1]);

  Int ans = 0;
  for(Int i=2; i<=n; i+=1) {
    Int val = 0;
    for(Int v=i; v>0; v/=10) {
      val += (v % 10).power(5);
    }
    if (val == i) {
      cerr << val << " " << i << endl;
      ans += i;
    }
  }
  cout << ans << nl;

  return 0;
}
