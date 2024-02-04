%:include "utility/nd_array.h"
%:include "utility/recursive.h"
%:include "main.h"
SOLVE() {
  int n;
  cin >> n;
  vector<int> a(n), b(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  for (int i = 0; i < n; i++) {
    cin >> b[i];
  }

  nd_array<char, 3> memo(n, n, n + 1, -1);
  auto solve = recursive([&](auto self, int ai, int bi, int len) -> bool {
    if (len == 0) return true;
    if (memo(ai, bi, len) != -1) return memo(ai, bi, len);
    memo(ai, bi, len) = false;
    for (int i = 0; i < len; i++) {
      if (a[ai] == b[bi + i] and self(ai + 1, bi, i) and
          self(ai + i + 1, bi + i + 1, len - 1 - i)) {
        memo(ai, bi, len) = true;
        break;
      }
    }
    return memo(ai, bi, len);
  });

  auto recover = recursive([&](auto self, int ai, int bi, int len) -> string {
    if (len == 0) return "";
    for (int i = 0; i < len; i++) {
      if (a[ai] == b[bi + i] and solve(ai + 1, bi, i) and
          solve(ai + i + 1, bi + i + 1, len - 1 - i)) {
        return "S" + self(ai + 1, bi, i) + "C" + self(ai + i + 1, bi + i + 1, len - 1 - i);
      }
    }
    assert(false);
  });

  if (solve(0, 0, n)) {
    cout << "YES" << nl;
    cout << recover(0, 0, n) << nl;
  } else {
    cout << "NO" << nl;
  }
}
