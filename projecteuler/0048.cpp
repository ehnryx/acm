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

  Int sum = 0;
  for(Int i=1; i<=n; i+=1) {
    sum += i.power(i);
  }
  Int ten = 10;
  cout << sum % ten.power(ten) << nl;

  return 0;
}
