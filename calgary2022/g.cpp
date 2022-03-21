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

  for(string s; cin >> s; ) {
    s.push_back(0);
    for(int i=0, j=0; i<size(s); i++) {
      if(s[i] != s[j]) {
        cout << i - j << s[j];
        j = i;
      }
    }
    cout << nl;
  }

  return 0;
}
