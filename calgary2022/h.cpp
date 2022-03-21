#include <bits/stdc++.h>
using namespace std;

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

  int a, b, c, d;
  cin >> a >> b >> c >> d;
  pt x(a, b), y(c, d);
  pt ans = x/y;
  cout << real(ans) << " " << imag(ans) << nl;

  return 0;
}
