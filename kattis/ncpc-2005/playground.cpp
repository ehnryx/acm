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

  for(int n; cin >> n && n; ) {
    auto a = cin.read<ld>(n);
    sort(begin(a), end(a));
    bool ok = false;
    for(int i=2; i<=n; i++) {
      vector<ll> v;
      transform(begin(a), begin(a) + i, back_inserter(v), [](ld x) { return llround(x*1e3); });
      ll sum = accumulate(begin(v), end(v), (ll)0);
      ll big = *max_element(begin(v), end(v));
      ok |= sum - big >= big;
    }
    if(ok) {
      cout << "YES" << nl;
    } else {
      cout << "NO" << nl;
    }
  }

  return 0;
}
