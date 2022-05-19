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

  int n;
  cin >> n;
  auto v = cin.read<pair<int, int>>(n);
  int ans = numeric_limits<int>::max();
  for(int bm=1; bm<1<<n; bm++) {
    int prod = 1, sum = 0;
    for(int i=0; i<n; i++) {
      if(bm & 1 << i) {
        prod *= v[i].first;
        sum += v[i].second;
      }
    }
    ans = min(ans, abs(prod - sum));
  }
  cout << ans << nl;

  return 0;
}
