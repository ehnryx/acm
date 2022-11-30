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


//#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  string a, b;
  cin >> a >> b;
  if(size(a) >= 1 and a[size(a) - 1] == 'e') {
    cout << a << "x" << b << nl;
  } else if(size(a) >= 1 and (
        a[size(a) - 1] == 'a' or
        a[size(a) - 1] == 'i' or
        a[size(a) - 1] == 'o' or
        a[size(a) - 1] == 'u')) {
    a.back() = 'e';
    cout << a << "x" << b << nl;
  } else if(size(a) >= 2 and a[size(a) - 1] == 'x' and a[size(a) - 2] == 'e') {
    cout << a << b << nl;
  } else {
    cout << a << "ex" << b << nl;
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
