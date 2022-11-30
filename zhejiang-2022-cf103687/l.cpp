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

  int n;
  cin >> n;
  vector<int> a(n);
  for_each(begin(a), end(a), [](auto& x) { cin >> x; });
  sort(begin(a), end(a));

  int ans = 0;
  ll sum = 0;
  for(int i=0, j=0; i<n; i++) {
    sum += a[i];
    while(j <= i && (ll)a[j] * (i+1) <= sum) {
      j++;
    }
    ans = max(ans, i - j + 1);
  }
  cout << ans << nl;

  return 0;
}
