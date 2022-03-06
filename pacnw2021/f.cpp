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
    bool peaked = false;
    for(int i=1; i<s.size(); i++) {
      if(s[i] < s[i-1]) peaked = true;
      if(peaked) s[i] = min(s[i], s[i-1]);
    }
    cout << s << nl;
  }

  return 0;
}
