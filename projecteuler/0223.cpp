#pragma GCC optimize("O3")

#include <bits/stdc++.h>
using namespace std;

#include "../../lca/number/int_base10.h"

constexpr char nl = '\n';
using ll = long long;
using Int = int_base10;

int main(int argc, char** argv) {
  cin.tie(0)->sync_with_stdio(0);

  ll n = 25'000'000;
  if (argc > 1) n = atoll(argv[1]);

  for(int a=2; a<=n; a++) {
    for(int b=a; b<=n; b++) {
      for(int c=b; c<=n; c++) {
        if(a*a + b*b == c*c + 1) {
          cout << a << " " << b << " " << c << nl;
        }
      }
    }
  }

  return 0;
}
