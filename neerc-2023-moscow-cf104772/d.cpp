%:include "main.h"
SOLVE() {
  int d;
  cin >> d;
  if (d == 1000) {
    cout << string(1000, '1') + "000" << nl;
  } else {
    auto s = to_string(d);
    for (int i = 0; i < d; i++) {
      cout << s;
    }
    cout << nl;
  }
}
