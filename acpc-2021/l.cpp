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

  static const int N = 1e4 + 1;
  vector<int> f(N);
  f[0] = f[1] = 1;
  for(int i=2; i<N; i++) {
    f[i] = f[i-1] + f[i-2];
    if(f[i] >= 1e6) f[i] -= 1e6;
  }

  int n;
  cin >> n;
  cout << f[n] << nl;

  return 0;
}
