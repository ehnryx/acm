#include <bits/stdc++.h>
using namespace std;

%:include "io/fast_input.h"

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());


int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#ifdef USING_FAST_INPUT
  fast_input cin;
#endif

  unordered_map<string, int> cnt;
  int maxv = 0;
  for (string s = cin.getline(); s != "***"; s = cin.getline()) {
    maxv = max(maxv, ++cnt[s]);
  }

  vector<string> ans;
  for(const auto& [s, c] : cnt) {
    if(c == maxv) {
      ans.push_back(s);
    }
  }

  if(size(ans) == 1) {
    cout << ans[0] << nl;
  } else {
    cout << "Runoff!" << nl;
  }

  return 0;
}
