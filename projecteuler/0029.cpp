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

  vector<Int> all, other;
  for(int a=2; a<=n; a++) {
    for(int b=2; b<=n; b++) {
      all.push_back(Int(a).power(Int(b)));
      other.push_back(Int(a).power(b));
    }
  }
  assert(all == other);
  sort(begin(all), end(all));
  cout << unique(begin(all), end(all)) - begin(all) << nl;

  return 0;
}
