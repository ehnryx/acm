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

  int n;
  cin >> n;
  ll a = 0;
  ll b = 1;
  for(int i=1; i<n; i++) {
    ll c = a + b;
    a = b;
    b = c;
  }
  cout << a << " " << b << nl;

  return 0;
}
