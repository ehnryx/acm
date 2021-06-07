#pragma GCC optimize("O3")

#include <bits/stdc++.h>
using namespace std;

#include "../../lca/number/int_base10.h"
#include "../../lca/number/fraction.h"

constexpr char nl = '\n';
using ll = long long;
using Int = int_base10;
using F = fraction<Int>;

int main(int argc, char** argv) {
  cin.tie(0)->sync_with_stdio(0);

  //ll n = 200;
  //if (argc > 1) n = atoll(argv[1]);

  F prod(1, 1);
  for(Int i=10; i<100; i+=1) {
    for(Int j=i+1; j<100; j+=1) {
      if(i % 10 == 0 && j % 10 == 0) continue;
      string a = i.str(), b = j.str(), c;
      sort(begin(a), end(a));
      sort(begin(b), end(b));
      set_intersection(begin(a), end(a), begin(b), end(b), back_inserter(c));
      if(c.size() != 1) continue;
      a.resize(set_difference(begin(a), end(a), begin(c), end(c), begin(a)) - begin(a));
      b.resize(set_difference(begin(b), end(b), begin(c), end(c), begin(b)) - begin(b));
      if(F(a[0] - '0', b[0] - '0') == F(i, j)) {
        prod *= F(i, j);
        cerr << "found " << i << " / " << j << nl;
      }
    }
  }
  cout << prod << nl;

  return 0;
}
