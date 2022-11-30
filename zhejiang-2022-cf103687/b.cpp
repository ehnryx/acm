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

  string s;
  cin >> s;
  string ans = s.substr(0, 2);
  for(int i=2; i<size(s); i++) {
    ans.push_back(s[i]);
    if(s[i-2] == 'c' && s[i-1] == 'j' && s[i] == 'b') {
      ans.push_back(',');
    }
  }
  cout << ans << nl;

  return 0;
}
