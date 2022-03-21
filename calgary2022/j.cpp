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

  int a, b;
  cin >> a >> b;
  int g = gcd(a, b);
  a /= g;
  b /= g;

  int twos = 0;
  int fives = 0;
  int d = b;
  while(d % 2 == 0) {
    d /= 2;
    twos++;
  }
  while(d % 5 == 0) {
    d /= 5;
    fives++;
  }
  if(d == 1) {
    cout << max(twos, fives) << " " << 0 << nl;
    return 0;
  }

  int ans = 1;
  ll tens = 10;
  while ((tens-1) % d != 0) {
    tens = tens * 10 % d;
    ans++;
  }

  cout << max(twos, fives) << " " << ans << nl;

  return 0;
}
