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
  int n, r;
  cin >> n >> r;

  vector<ld> lf((1<<n) + 1);
  for(int i=1; i<=1<<n; i++) {
    lf[i] = lf[i-1] + log((ld)i);
  }

  auto choose = [&](int N, int R) {
    if(R < 0 or N < R) throw logic_error("");
    return lf[N] - lf[R] - lf[N-R];
  };

  ld ans = 0;
  for(int i=1; i<=n; i++) {
    int s = 1<<i;
    try {
      ans += exp(choose((1<<n) - r, s-1) - choose((1<<n) - 1, s-1));
    } catch(...) {}
  }
  cout << ans << nl;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(5);
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
