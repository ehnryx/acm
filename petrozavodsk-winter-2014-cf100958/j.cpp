#include "../../lca/number/mod_int.h"
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int MOD = 1e9 + 7;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

using Int = mod_int<MOD>;

Int volume(Int a, Int b, int height) {
  return a * height - b * (height - 1);
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);

  int n;
  cin >> n;
  vector<int> a(n+1);
  for(int i=1; i<=n; i++) {
    cin >> a[i];
  }
  int s;
  cin >> s;

  vector f(s + 1, vector(n + 1, vector<Int>(300 + 1)));
  for(int k=1; k<=s; k++) {
    for(int i=1; i<=a[1]; i++) {
      f[k][1][i] = min(k, i);
    }
    for(int L=2; L<=n; L++) {
      for(int i=1; i<=a[L]; i++) {
        f[k][L][i] = volume(f[k][L-1][a[L-1]], f[k-1][L-1][a[L-1]], k) + f[k-1][L][i-1];
      }
    }
  }
  cout << f[s][n][a[n]] << nl;

  return 0;
}

/* do more math
 * f(k, a, b...) = volume of dimensions
 * base case:
 *    f(k, a) = min(k, a)
 *    f(0, a, ...) = 0
 *    f(k, 0, ...) = 0
 * f(k, a, b...) = V[f(k, b...), f(k - 1, b...)] + f(k-1, a-1, b...)
 * f(k, L, a) = V[f(k, L - 1, b), f(k - 1, L - 1, b)] + f(k - 1, L, a - 1)
 */

/* volume calculations
 * A -> B in 1 unit (volumes)
 * A^{1/{d-1}} -> B^{1/{d-1}} in 1 unit (lengths)
 * let a = A^{1/{d-1}} and b = B^{1/{d-1}}
 * a -> 0 in a / (a - b) units
 * so h = a / (a - b)
 * V = h*A/d - (h-1)*B/d
 */
