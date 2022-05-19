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

  int n;
  cin >> n;
  auto v = cin.read<int>(n, 5);
  map<vector<int>, int> cnt;
  for(auto& it : v) {
    sort(begin(it), end(it));
    cnt[it]++;
  }

  int val = 0;
  int ans = 0;
  for(const auto& [_, it] : cnt) {
    if(it > val) {
      val = it;
      ans = 0;
    }
    ans += (it == val) * val;
  }
  cout << ans << nl;

  return 0;
}
