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
  int ans = 0;
  for(int i=0; i<n; i++) {
    string v;
    cin >> v;
    ans += pow(stoi(v.substr(0, size(v) - 1)), stoi(v.substr(size(v) - 1)));
  }
  cout << ans << nl;

  return 0;
}
