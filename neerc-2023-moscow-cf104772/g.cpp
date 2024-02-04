%:include "utility/nd_array.h"
%:include "main.h"
SOLVE() {
  int n, p, m;
  cin >> n >> p >> m;
  static constexpr int A = 512;
  int const rem = n - p;
  nd_array<ll, 2> dp(rem + 1, A);
  dp(0, p) = 1;
  for (int s = 1; s <= rem; s++) {
    for (int i = s; i <= rem; i++) {
      for (int r = 0; r < A; r++) {
        dp(i, r) += dp(i - s, r ^ s);
        if (dp(i, r) >= m) dp(i, r) -= m;
      }
    }
  }
  cout << dp(rem, 0) << nl;
}
