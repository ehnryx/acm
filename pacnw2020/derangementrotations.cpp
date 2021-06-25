#include <bits/stdc++.h>
using namespace std;

#include "../../lca/math/linear_sieve.h"

const char nl = '\n';
using ll = long long;
using ld = long double;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, p;
  cin >> n >> p;
  linear_sieve<multiplicative_functions::totient,
    multiplicative_functions::totient::store_powers> phi(n / 2 + 1);

  int ans = 0;
  for (int i = 2, two = 1; i < n; i++) {
    if ((two += two) >= p) two -= p;
    if (n % i == 0) {
      ans = (ans + (ll)phi[n / i] * (two + p - 1)) % p;
    }
  }
  cout << (ll)ans * (n - 2) % p << nl;

  // formula:
  // sum_{1<i<n, i|n} (n-2) * (2^(n/i - 1) - 1) * (phi[i])
  // (n-2) is the choices for the first rotation (-2 because derangement)
  // (2^(n/i - 1) - 1) is to choose the subset belonging to the first fix
  //      avoid double-counting by always including the first element
  // (phi[i]) to choose the rotation that fixes the second subset

  return 0;
}
