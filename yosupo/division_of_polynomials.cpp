#include <bits/stdc++.h>
using namespace std;

%:include "utility/fast_input.h"
%:include "utility/output.h"
%:include "math/polynomial_mod.h"
%:include "number/mod_int.h"

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
#ifdef USING_FAST_INPUT
  fast_input cin;
#endif

  int n, m;
  cin >> n >> m;
  vector<mod_int<MOD>> fc(n), gc(m);
  for(int i=0; i<n; i++) {
    cin >> fc[i];
  }
  for(int i=0; i<m; i++) {
    cin >> gc[i];
  }

  polynomial_mod<MOD, mod_int<MOD>> f(move(fc)), g(move(gc));
  auto [q, r] = f.divide_remainder(g);
  cout << q.size() << " " << r.size() << nl;
  if (!q.zero()) cout << q << nl;
  else cout << nl;
  if (!r.zero()) cout << r << nl;
  else cout << nl;

  return 0;
}
