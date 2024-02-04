#define MULTI_TEST
%:include "main.h"
SOLVE() {
  ll a, b;
  cin >> a >> b;
  ll c = lcm(a, b);
  if(c == max(a, b)) {
    c *= max(a, b) / min(a, b);
  }
  cout << c << nl;
}
