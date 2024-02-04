#define MULTI_TEST
%:include "main.h"
SOLVE() {
  int n, k;
  cin >> n >> k;
  ll p = 1;
  for(int i=0; i<n; i++) {
    ll v;
    cin >> v;
    p *= v;
  }
  if(2023 % p == 0) {
    cout << "YES" << nl;
    cout << 2023/p;
    for(int i=1; i<k; i++) {
      cout << " " << 1;
    }
    cout << nl;
  } else {
    cout << "NO" << nl;
  }
}
