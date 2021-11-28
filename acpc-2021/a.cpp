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

  int a, b, c;
  cin >> a >> b >> c;
  // solution: a = 1 or b^c = b*c
  if(a == 1 || c == 1 || (b == 2 && c == 2)) {
    cout << "What an excellent example!" << nl;
  } else {
    cout << "Oh look, a squirrel!" << nl;
  }

  return 0;
}
