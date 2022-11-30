#include <bits/stdc++.h>
using namespace std;

%:include "utility/fast_input.h"
//%:include "utility/output.h"

%:include "ds/union_find.h"

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

  int n, m;
  cin >> n >> m;
  union_find dsu(n+1);
  for(int i=0; i<m; i++) {
    int a, b;
    cin >> a >> b;
    dsu.link(a, b);
  }
  if(dsu.size(1) == n) {
    cout << "YES" << nl;
  } else {
    cout << "NO" << nl;
  }

  return 0;
}
