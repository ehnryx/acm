#define MULTI_TEST
%:include "main.h"
SOLVE() {
  ll n;
  cin >> n;
  for (int i = 1; i <= 99; i++) {
    if (__builtin_popcountll(n + i) <= i) {
      return void(cout << i - 1 << nl);
    }
  }
  assert(false);
}
