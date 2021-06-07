#pragma GCC optimize("O3")

#include <bits/stdc++.h>
using namespace std;

#include "../../lca/number/int_base10.h"

constexpr char nl = '\n';
using ll = long long;
using Int = int_base10;

int main(int argc, char** argv) {
  cin.tie(0)->sync_with_stdio(0);

  //ll n = 100;
  //if (argc > 1) n = atoll(argv[1]);

  Int num = Int(28433) * Int(2).pow(7830457) + 1;
  cout << num % Int(10).pow(10) << nl;

  return 0;
}
