#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
//%:include "utility/output.h"

using ll = long long;
using ld = long double;

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

  int n, m, x;
  cin >> n >> m >> x;
  vector<int> b(n), a(m);
  for_each(begin(b), end(b), [](auto& v) { cin >> v; });
  for_each(begin(a), end(a), [](auto& v) { cin >> v; });
  int ans =
    count_if(begin(b), end(b), [x](auto v) { return v >= x; }) +
    count_if(begin(a), end(a), [x](auto v) { return v <= x; });
  cout << ans << nl;

  return 0;
}
