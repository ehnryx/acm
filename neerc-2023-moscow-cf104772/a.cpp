%:include "main.h"
SOLVE() {
  int a, b, c, d;
  cin >> a >> b >> c >> d;
  vector v = {a, b, c, d};
  sort(begin(v), end(v));
  cout << v[0] * v[2] << nl;
}
