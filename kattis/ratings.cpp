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

  vector ncr(60, vector<ll>(60));
  for(int i=0; i<60; i++) {
    ncr[i][0] = ncr[i][i] = 1;
    for(int j=1; j<i; j++) {
      ncr[i][j] = ncr[i-1][j] + ncr[i-1][j-1];
    }
  }

  for(int n; cin >> n && n; ) {
    vector<int> a(n);
    for(int i=0; i<n; i++) {
      cin >> a[i];
    }

    ll ans = 1ll;

    int sum = accumulate(begin(a), end(a), 0);
    for(int s=0; s<sum; s++) {
      ans += ncr[s+n-1][n-1];
    }

    for(int e=0; e+1<n; e++) {
      int equal = accumulate(begin(a), begin(a)+e, 0);
      for(int v=0; v<a[e]; v++) {
        int rem = sum - equal - v;
        int left = n-e - 1;
        ans += ncr[rem+left-1][left-1];
      }
    }

    cout << ans << nl;
  }

  return 0;
}
