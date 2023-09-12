#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
%:include "utility/output.h"

using ll = long long;
using ld = long double;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());


#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  int x;
  cin >> x;
  vector<int> ans = {x};
  for(int i=0; i<30; i++) {
    if((x & 1<<i) and (x > 1<<i)) {
      x -= 1<<i;
      ans.push_back(x);
    }
  }
  for(int i=30; i>=0; i--) {
    if(x > 1<<i) {
      x -= 1<<i;
      ans.push_back(x);
    }
  }
  cout << size(ans) << nl;
  cout << ans << nl;
  assert(x == 1);
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
