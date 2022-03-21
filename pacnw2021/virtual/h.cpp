#include <bits/stdc++.h>
using namespace std;

#include "../../lca/string/suffix_array_lcp.h"

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());


int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);

  string s;
  cin >> s;
  int n = s.size();
  string rev = s;
  reverse(begin(rev), end(rev));

  suffix_array_lcp sa(s + "." + rev + rev);
  bool ok = true;
  for(int i=0; i<n; i++) {
    int len = n - i;
    if(len == n) len--;
    bool found = false;
    for(int j=0; j<2*n; j++) {
      found |= (sa.lcp(i, n+1 + j) >= len);
    }
    ok &= found;
  }
  cout << ok << nl;

  return 0;
}
