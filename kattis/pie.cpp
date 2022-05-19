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

  int T;
  cin >> T;
  while(T--) {
    int n, f;
    cin >> n >> f;
    vector<ld> a(n);
    for(int i=0; i<n; i++) {
      int r;
      cin >> r;
      a[i] = r*r*M_PIl;
    }

    ld l = 0;
    ld r = *max_element(begin(a), end(a));
    for(int bs=0; bs<99; bs++) {
      ld m = (l + r) / 2;
      int cnt = 0;
      for(int i=0; i<n; i++) {
        cnt += floor(a[i] / m);
      }
      if(f+1 <= cnt) {
        l = m;
      } else {
        r = m;
      }
    }
    cout << l << nl;
  }

  return 0;
}
