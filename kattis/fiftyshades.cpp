#include <bits/stdc++.h>
using namespace std;

//%:include "io/fast_input.h"

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
    string s;
    cin >> s;
    for(char& c : s) {
      c = tolower(c);
    }
    ans += (s.find("pink") != -1 || s.find("rose") != -1);
  }

  if(ans) {
    cout << ans << nl;
  } else {
    cout << "I must watch Star Wars with my daughter" << nl;
  }

  return 0;
}
