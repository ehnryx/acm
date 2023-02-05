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


#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  int x[3], y[3];
  for(int i=0; i<3; i++) {
    cin >> x[i] >> y[i];
  }
  int h = (x[0] == x[1] || x[1] == x[2] || x[2] == x[0]);
  int v = (y[0] == y[1] || y[1] == y[2] || y[2] == y[0]);
  if(h && v) {
    cout << "NO" << nl;
  } else {
    cout << "YES" << nl;
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
