%:include "utility/output.h"
#define MULTI_TEST
%:include "main.h"
SOLVE() {
  int n;
  cin >> n;
  vector<ll> ans;
  ll sum = 0;
  int odd = 0;
  for(int i=1; i<=n; i++) {
    int v;
    cin >> v;
    sum += v;
    odd += v % 2;
    int full = odd / 3;
    int rem = odd - full * 3;
    if(rem == 1) full += 1;
    full = min(full, i - 1);
    ans.push_back(sum - full);
  }
  cout << ans << nl;
}
