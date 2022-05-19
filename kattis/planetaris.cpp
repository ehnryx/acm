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


int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#ifdef USING_FAST_INPUT
  fast_input cin;
#endif

  int n, m;
  cin >> n >> m;
  auto v = cin.read<int>(n);
  sort(begin(v), end(v));
  int ans = 0;
  for(int it : v) {
    if(it + 1 <= m) {
      ans++;
      m -= it + 1;
    }
  }
  cout << ans << nl;

  return 0;
}
