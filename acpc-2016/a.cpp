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
    string s;
    cin >> s;
    int ans = 0;
    int res = 0;
    for(char c : s) {
      res = res * 10 + c - '0';
      //ans = max(ans, popcount((unsigned int)res));
      ans = max(ans, __builtin_popcount(res));
    }
    cout << ans << nl;
  }

  return 0;
}
