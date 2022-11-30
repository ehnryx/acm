#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
//%:include "utility/output.h"

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

  int a, b;
  cin >> a >> b;
  int ans = 0;
  while(a > b) {
    if(a % 2) {
      a++;
      ans++;
    }
    a /= 2;
    ans++;
  }
  cout << ans + (b-a) << nl;

  return 0;
}
