%:include "utility/output.h"
#define MULTI_TEST
%:include "main.h"
SOLVE() {
  int n, k;
  cin >> n >> k;
  vector<int> ans(n);
  iota(begin(ans), begin(ans) + k + 1, n - k);
  iota(rbegin(ans), rbegin(ans) + n - k - 1, 1);
  cout << ans << nl;
}
