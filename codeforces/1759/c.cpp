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
  int l, r, x;
  cin >> l >> r >> x;
  int a, b;
  cin >> a >> b;

  if(a == b) {
    return void(cout << 0 << nl);
  }

  if(abs(a - b) >= x) {
    return void(cout << 1 << nl);
  }

  if((abs(a - l) >= x and abs(b - l) >= x) or
      (abs(a - r) >= x and abs(b - r) >= x)) {
    return void(cout << 2 << nl);
  }

  if(abs(l - r) >= x and
      (abs(a - l) >= x or abs(a - r) >= x) and
      (abs(b - l) >= x or abs(b - r) >= x)) {
    return void(cout << 3 << nl);
  }

  cout << -1 << nl;
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
