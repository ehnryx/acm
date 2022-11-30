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

  int T;
  cin >> T;
  while(T--) {
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    for(int i=0; i<n; i++) {
      cin >> a[i];
    }
    adjacent_difference(begin(a), end(a), begin(b));
    if(unique(begin(b)+1, end(b)) - (begin(b)+1) == 1) {
      cout << "arithmetic" << nl;
    } else if(sort(begin(a), end(a)), adjacent_difference(begin(a), end(a), begin(b));
        unique(begin(b)+1, end(b)) - (begin(b)+1) == 1) {
      cout << "permuted arithmetic" << nl;
    } else {
      cout << "non-arithmetic" << nl;
    }
  }

  return 0;
}
