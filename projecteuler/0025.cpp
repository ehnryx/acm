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

  Int a = 1, b = 0;
  int i = 1;
  while(a.length() < n) {
    Int c = a + b;
    assert(c - a == b);
    assert(c - b == a);
    assert(a <= c);
    assert(b < c);
    b = a;
    a = c;
    i++;
    //cerr << i << ": " << c << nl;
  }
  cout << i << nl;

  return 0;
}
