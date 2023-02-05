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
  int a, b, c;
  cin >> a >> b >> c;
  vector<function<int(int, int)>> funcs = {
    plus<int>(),
    minus<int>(),
    multiplies<int>(),
    [](int x, int y) {
      if (x % y == 0) return x / y;
      throw invalid_argument("verboden");
    },
  };

  int ans = a + b + c;
  for(auto f : funcs) {
    try {
      int val = f(a, b);
      for(auto g : funcs) {
        try {
          int res = g(val, c);
          if(res >= 0) {
            ans = min(ans, res);
          }
        } catch(const invalid_argument&) {}
      }
    } catch(const invalid_argument&) {}
  }

  cout << ans << nl;
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
