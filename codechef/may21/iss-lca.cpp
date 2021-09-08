#include <bits/stdc++.h>
using namespace std;

#include "../../../lca/math/linear_sieve.h"

constexpr char nl = '\n';

struct func {
  using T = pair<long long, int>;
  static constexpr bool store_powers = true;
  static T one() { return T(1, 1); }
  static T prime(int p) { return T(2*p - 1, p - 1); }
  static T coprime(T a, T b) { return T(a.first * b.first, a.second * b.second); }
  static T prime_power(T f, int p, int) {
    return T((f.first + f.second) * p, f.second * p);
  }
};

// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#if defined(ONLINE_JUDGE) && defined(FILENAME)
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif

  static const int N = 4e6 + 2;
  linear_sieve<func> sieve(N);

  int T;
  cin >> T;
  while(T--) {
    int k;
    cin >> k;
    int n = 4*k + 1;
    cout << n + (sieve[n].first - n) / 2 - 1 << nl;
  }

  return 0;
}
