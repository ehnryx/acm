#include <bits/stdc++.h>
using namespace std;

//%:include "utility/defines.h"
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

  const int M = 360 * 60 * 60;

  int T;
  cin >> T;
  while(T--) {
    int r, n, q, m, s;
    cin >> r >> n >> q >> m >> s;
    vector<bool> cut(M + 1);
    for(int i=0, at=0; i<n && !cut[at]; i++) {
      cut[at] = true;
      at += q * 60 * 60 + m * 60 + s;
      if(at >= M) at -= M;
    }
    cut[M] = true;
    int ans = 0;
    for(int i=0, last=0; i<=M; i++) {
      if(cut[i]) {
        ans = max(ans, i - last);
        last = i;
      }
    }
    cout << M_PIl * r * r * ans / M << nl;
  }

  return 0;
}
