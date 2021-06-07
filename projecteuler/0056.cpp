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

  Int ans = 0;
  for(Int a=1; a<n; a+=1) {
    for(Int b=1; b<n; b+=1) {
      Int sum = 0;
      for(char c : a.power(b).str()) {
        sum += c - '0';
      }
      ans = max(ans, sum);
    }
  }
  cout << ans << nl;

  return 0;
}
