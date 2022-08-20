#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
//%:include "utility/output.h"
%:include "string/suffix_array_lcp.h"

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

  int m, n;
  cin >> m >> n;
  string all;
  for(int i=0; i<n; i++) {
    string s;
    cin >> s;
    s.resize(2 * s.size(), '$');
    all += s;
  }
  suffix_array_lcp sa(all);

  int l = 1;
  int r = m + 1;
  while(l < r) {
    int len = (l + r) / 2;
    int good = 0;
    for(int i=0; i<m; i++) {
      int at = sa.rank[i];
      bool ok = true;
      for(int j=at-1; j>0; j--) {
        if(sa[j] >= 2*m) {
          ok &= (sa.lcp(i, sa[j]) < len);
          break;
        }
      }
      for(int j=at+1; j<sa.sa.size(); j++) {
        if(sa[j] >= 2*m) {
          ok &= (sa.lcp(i, sa[j]) < len);
          break;
        }
      }
      good += ok;
    }
    if(2*good >= m) {
      r = len;
    } else {
      l = len + 1;
    }
  }

  cout << (r <= m ? r : -1) << nl;

  return 0;
}
