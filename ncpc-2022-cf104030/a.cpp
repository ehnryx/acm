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
  int n;
  scanf("%d", &n);
  int a = 0;
  int b = 0;
  bool done = false;
  for(int i=1; i<=n; i++) {
    int x, y;
    scanf("%d-%d", &x, &y);
    if(max(x, y) > 11 or min(x, y) == 11) {
      return void(cout << "error " << i << nl);
    }
    if(done) {
      if(x != a or y != b) {
        return void(cout << "error " << i << nl);
      }
      continue;
    }
    if((x + y) % 4 == 1 or (x + y) % 4 == 2) {
      if(x < a or y < b) {
        return void(cout << "error " << i << nl);
      }
      a = x;
      b = y;
    } else {
      if(y < a or x < b) {
        return void(cout << "error " << i << nl);
      }
      a = y;
      b = x;
    }
    if(max(x, y) == 11) {
      done = true;
      a = x;
      b = y;
    }
  }
  cout << "ok" << nl;
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
