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

struct Country {
  int a, b;
  Country operator + (const Country& o) const {
    return Country{ a + o.a, b + o.b };
  }
  template <size_t B>
  void fast_read(fast_input<B>& in) {
    in >> a >> b;
  }
};

ll nc2(int n) {
  return (ll)n * (n-1) / 2;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#ifdef USING_FAST_INPUT
  fast_input cin;
#endif

  int n;
  cin >> n;
  auto v = cin.read<Country>(n);
  /*
  vector<Country> v(n);
  for(int i=0; i<n; i++) {
    cin >> v[i].a >> v[i].b;
  }
  */
  Country sum = accumulate(begin(v), end(v), Country{0, 0});

  ll ans = nc2(sum.a) * sum.b;
  for(auto [a, b] : v) {
    ans -= nc2(a) * (sum.b - b);
    ans -= (ll)a * b * (sum.a - a);
    ans -= nc2(a) * b;
  }
  cout << ans << nl;

  return 0;
}
