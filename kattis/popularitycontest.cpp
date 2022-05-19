#include <bits/stdc++.h>
using namespace std;

%:include "utility/fast_input.h"

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
  vector<int> ans(n+1);
  iota(begin(ans), end(ans), 0);
  for(int i=0; i<m; i++) {
    int a, b;
    cin >> a >> b;
    ans[a]--;
    ans[b]--;
  }
  for(int i=1; i<=n; i++) {
    cout << -ans[i] << " ";
  }
  cout << nl;

  return 0;
}
