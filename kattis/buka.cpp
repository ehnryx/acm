#include <bits/stdc++.h>
using namespace std;

%:include "io/fast_input.h"

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

  fast_input cin;

  string a, b, op;
  cin >> a >> op >> b;

  if(op == "*") {
    cout << 1 << string(a.size() + b.size() - 2, '0') << nl;
  } else {
    if(a.size() < b.size()) swap(a, b);
    a[(a.size() - b.size())] += 1;
    cout << a << nl;
  }

  return 0;
}
