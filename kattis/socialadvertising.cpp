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

  int T;
  cin >> T;
  while(T--) {
    int n;
    cin >> n;
    vector<int> bm(n);
    for(int i=0; i<n; i++) {
      int m;
      cin >> m;
      for(int j=0; j<m; j++) {
        int v;
        cin >> v;
        bm[i] |= 1 << (v-1);
      }
      bm[i] |= 1 << i;
    }
    vector<int> cnt(1<<n, n);
    cnt[0] = 0;
    for(int i=1; i<1<<n; i++) {
      for(int b : bm) {
        cnt[i] = min(cnt[i], 1 + cnt[i & ~b]);
      }
    }
    cout << cnt[(1<<n)-1] << nl;
  }

  return 0;
}
