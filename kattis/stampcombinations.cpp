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
  auto a = cin.read<int>(n);
  int sum = accumulate(begin(a), end(a), 0);

  while(m--) {
    int v;
    cin >> v;
    bool ok = false;
    for(int i=0, j=0, have=sum; i<n; i++) {
      while(j < i || (j < n && have > v)) {
        have -= a[j++];
      }
      if(have == v) {
        ok = true;
        break;
      }
      have += a[i];
    }
    cout << (ok ? "Yes" : "No") << nl;
  }

  return 0;
}
