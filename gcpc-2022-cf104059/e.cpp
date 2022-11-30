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
  static constexpr int M = 1e5 + 1;
  vector<ld> ans(M);
  ans[1] = 1;
  ans[2] = 0;
  for(int i=3; i<M; i++) {
    ans[i] = (ans[i-1] + ans[i-2]) / 2;
  }

  ll n;
  cin >> n;
  ld v = 100 * (n < M ? ans[n] : ans.back());
  cout << v << " " << 100-v << nl;
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
