#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
//%:include "utility/output.h"

%:include "ds/union_find.h"

using ll = long long;
using ld = long double;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());


//#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  int n;
  cin >> n;
  vector f(n+1, vector<ll>(n+1));
  vector<tuple<ll, int, int>> ev;
  for(int i=1; i<=n; i++) {
    for(int j=1; j<=i; j++) {
      cin >> f[i][j];
      if(i != j) {
        ev.emplace_back(f[i][j], i, j);
      }
    }
  }
  sort(begin(ev), end(ev), greater<>());

  union_find dsu(n+1);
  for(auto [fij, i, j] : ev) {
    if(dsu[i] == dsu[j]) continue;
    ll eij = (f[i][i] + f[j][j] - 2*fij) / n;
    dsu.link(i, j);
    cout << j << " " << i << " " << eij << nl;
  }
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#ifdef USING_FAST_INPUT
  fast_input cin;
#endif

  int T = 1;
#ifdef MULTI_TEST
  cin >> T;
#endif
  for(int testnum=1; testnum<=T; testnum++) {
    solve_main(testnum, cin);
  }

  return 0;
}
