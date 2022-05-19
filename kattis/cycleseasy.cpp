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

  int T;
  cin >> T;
  for(int testnum=1; testnum<=T; testnum++) {
    int n, m;
    cin >> n >> m;

    vector bad(n, vector<bool>(n));
    for(auto [a, b] : cin.read<pair<int, int>>(m)) {
      bad[a-1][b-1] = true;
      bad[b-1][a-1] = true;
    }

    vector<int> order(n);
    iota(begin(order), end(order), 0);
    int ans = 0;
    do {
      bool ok = true;
      for(int i=n-1, j=0; j<n; i=j++) {
        ok &= !bad[order[i]][order[j]];
      }
      ans += ok;
    } while(next_permutation(begin(order), end(order)));
    cout << "Case #" << testnum << ": " << ans / n / 2 % 9901 << nl;
  }

  return 0;
}
