#include <bits/stdc++.h>
using namespace std;

%:include "utility/fast_input.h"
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

  int T;
  cin >> T;
  while(T--) {
    int n;
    cin >> n;
    auto a = cin.read<int>(n);
    auto m = max_element(begin(a), end(a));
    int sum = accumulate(begin(a), end(a), 0);
    if(2 * (*m) > sum) {
      cout << "majority winner " << (m - begin(a)) + 1 << nl;
    } else if(count(begin(a), end(a), *m) == 1) {
      cout << "minority winner " << (m - begin(a)) + 1 << nl;
    } else {
      cout << "no winner" << nl;
    }
  }

  return 0;
}
