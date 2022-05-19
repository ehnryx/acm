#include <bits/stdc++.h>
using namespace std;

%:include "utility/fast_input.h"

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
  auto g = cin.read<char, 1, 1>(n, m);
  vector<string> all;
  for(int i=1; i<=n; i++) {
    for(int j=1; j<=m; j++) {
      if(!isalpha(g[i][j])) continue;
      if(!isalpha(g[i-1][j])) {
        string s;
        for(int k=i; isalpha(g[k][j]); k++) {
          s.push_back(g[k][j]);
        }
        if(size(s) > 1) all.push_back(s);
      }
      if(!isalpha(g[i][j-1])) {
        string s;
        for(int k=j; isalpha(g[i][k]); k++) {
          s.push_back(g[i][k]);
        }
        if(size(s) > 1) all.push_back(s);
      }
    }
  }
  cout << *min_element(begin(all), end(all)) << nl;

  return 0;
}
