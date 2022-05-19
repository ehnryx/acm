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

  int T;
  cin >> T;
  while(T--) {
    int r, e, c;
    cin >> r >> e >> c;
    if(r < e - c) {
      cout << "advertise" << nl;
    } else if(r > e - c) {
      cout << "do not advertise" << nl;
    } else {
      cout << "does not matter" << nl;
    }
  }

  return 0;
}
