#include <bits/stdc++.h>
using namespace std;

%:include "utility/fast_input.h"
%:include "utility/output.h"

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

  int n, m;
  cin >> n >> m;
  auto a = cin.read<pair<int, int>>(n);
  multiset<int> have, opt;
  int ans = 0, best = 0;
  for(auto [t, len] : a) {
    while(!empty(have) && *begin(have) <= t) {
      have.erase(begin(have));
      ans++;
    }
    if(size(have) < m) {
      have.insert(t + len);
    }
    while(!empty(opt) && *begin(opt) <= t) {
      opt.erase(begin(opt));
      best++;
    }
    opt.insert(t + len);
    if(size(opt) > m) {
      opt.erase(prev(end(opt)));
    }
    cout << best + size(opt) - (ans + size(have)) << nl;
  }

  return 0;
}
