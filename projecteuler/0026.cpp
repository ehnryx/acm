#pragma GCC optimize("O3")

#include <bits/stdc++.h>
using namespace std;

#include "../../lca/number/int_base10.h"

constexpr char nl = '\n';
using ll = long long;

using Int = int_base10;

int main(int argc, char** argv) {
  cin.tie(0)->sync_with_stdio(0);

  ll n = 1'000;
  if (argc > 1) n = atoll(argv[1]);

  pair<int,Int> ans(0, 0);
  for(Int d=2; d<n; d+=1) {
    assert(gcd(d, Int(10)) == gcd(d.value<ll>(), 10));
    if(gcd(d, Int(10)) > 1) continue;
    Int v = 9;
    while(v%d != 0) {
      v = v*10 + 9;
    }
    ans = max(ans, pair(v.length(), d));
  }
  cout << ans.second << ": length " << ans.first << nl;

  return 0;
}
