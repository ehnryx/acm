#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
//%:include "utility/output.h"

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
  string s;
  cin >> s;
  int ans = 0;
  for(int i=0; i<n; i++) {
    if(s[i] != '0') {
      ans++;
      if(i+2 < n && s[i+1] != '0') {
        s[i+1] = '0';
        s[i+2] = '1';
      }
    }
  }
  cout << ans << nl;

  return 0;
}
