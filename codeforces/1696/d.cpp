#include <bits/stdc++.h>
using namespace std;

//%:include "utility/defines.h"
//%:include "utility/fast_input.h"
//%:include "utility/output.h"

%:include "ds/range_minimum_query.h"

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

  int T;
  cin >> T;
  while(T--) {
    int n;
    cin >> n;
    vector<pair<int, int>> a(n);
    for(int i=0; i<n; i++) {
      cin >> a[i].first;
      a[i].second = i;
    }
    range_minimum_query<pair<int, int>> smin(a);
    range_minimum_query<pair<int, int>, greater<>> smax(a);
    int cnt = 0;
    for(int i=0; i!=n-1; ) {
      int l = i+1;
      int r = n-1;
      while(l < r) {
        int m = (l+r + 1) / 2;
        int bot = smin.query(i, m).first;
        int top = smax.query(i, m).first;
        if(top == a[i].first || bot == a[i].first) {
          l = m;
        } else {
          r = m-1;
        }
      }
      i = max(smax.query(i, r).second, smin.query(i, r).second);
      cnt++;
    }
    cout << cnt << nl;
  }

  return 0;
}
