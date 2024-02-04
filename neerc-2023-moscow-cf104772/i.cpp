%:include "utility/recursive.h"

%:include "main.h"
#include <cassert>
SOLVE() {
  int n;
  cin >> n;
  int visible, old;
  cin >> visible;

  auto flip = [&](int l, int r) {
    cout << l << " " << r << endl;
    old = visible;
    cin >> visible;
    if (visible == n) {
      exit(0);
    }
  };

  auto get_visible = [&](int l, int r) {
    vector<int> have;
    have.push_back(l - 1);
    for (int i = l; i <= r; i++) {
      flip(i, i);
      if (visible < old) {
        have.push_back(i);
        flip(i, i);
      } else if (visible > old) {
        have.push_back(i);
      }
    }
    have.push_back(r + 1);
    return have;
  };

  auto solve = recursive([&](auto self, int l, int r) -> void {
    if (l > r) return;
    int len = r - l + 1;
    for (int i = 1; i < 1 << len; i++) {
      int cur = __builtin_ctz(i);
      flip(l, l + cur);
      assert(visible >= old);
      if (visible > old) {
        break;
      }
    }
    auto have = get_visible(l, r);
    for (int i = 1; i < size(have); i++) {
      self(have[i - 1] + 1, have[i] - 1);
    }
  });

  auto have = get_visible(1, n);
  for (int i = 1; i < size(have); i++) {
    solve(have[i - 1] + 1, have[i] - 1);
  }
}
