#include <bits/stdc++.h>
using namespace std;

#include "../../../lca/string/hash_polynomial.h"
#include "../../../lca/string/hash_multi.h"

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

using Hasher = hash_multi<
  hash_polynomial,
  (int)1e9+7, 31,
  (int)1e9+9, 37,
  (int)1e9+123, 97,
  (int)1e9+321, 101>;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);

  int T;
  cin >> T;
  while(T--) {
    string s;
    cin >> s;
    int n = size(s);
    Hasher ha(s);
    reverse(begin(s), end(s));
    Hasher hb(s);

    int take = 0;
    for(int i=1; 2*i<=n && s[i-1] == s[n-i]; i++) {
      take++;
    }

    pair<int, int> mid(0, 0);
    for(int i=1; i+2*take<=n; i++) {
      if(ha.get(take, i) == hb.get(n - take - i, i)) {
        mid = max(mid, pair(i, n - take - i));
      }
      if(ha.get(n - take - i, i) == hb.get(take, i)) {
        mid = max(mid, pair(i, take));
      }
    }

    cout << s.substr(0, take) + s.substr(mid.second, mid.first) + s.substr(n - take, take) << nl;
  }

  return 0;
}
