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

  int T;
  cin >> T;
  for(int testnum=1; testnum<=T; testnum++) {
    int n, f, m;
    cin >> n >> f >> m;
    auto a = cin.read<int>(m);
    sort(begin(a), end(a), greater<>());
    ll ans = 0;
    for(int i=0; i<n; i++) {
      for(int j=0; j<f; j++) {
        if(i*f+j >= m) {
          goto work;
        }
        ans += (ll)(i+1) * a[i*f+j];
      }
    }
work:
    cout << "Case #" << testnum << ": " << ans << nl;
  }

  return 0;
}
