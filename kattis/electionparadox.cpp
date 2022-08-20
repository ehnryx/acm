#include <bits/stdc++.h>
using namespace std;

%:include "utility/defines.h"
%:include "utility/fast_input.h"
%:include "utility/output.h"

using ll = long long;
using ld = long double;

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
  auto v = cin.read<int>(n);
  sort(begin(v), end(v));
  int ans = 0;
  for(int i=0; i<n; i++) {
    if(i <= n/2) {
      ans += v[i] / 2;
    } else {
      ans += v[i];
    }
  }
  cout << ans << nl;

  return 0;
}
