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

  for(int n; cin >> n && n != -1; ) {
    auto a = cin.read<pair<int, int>, 1>(n);
    int ans = 0;
    for(int i=1; i<=n; i++) {
      ans += a[i].first * (a[i].second - a[i-1].second);
    }
    cout << ans << " miles" << nl;
  }

  return 0;
}
