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
  cin >> n;
  vector<ll> a(n+1);
  for(int i=1; i<=n; i++) {
    cin >> a[i];
  }
  vector<ll> sum(n+1);
  partial_sum(begin(a), end(a), begin(sum));
  int last = n;
  for(int i=1; i<=n; i++) {
    if(sum[i] < i) {
      last = i;
      break;
    }
  }
  ll ans = 0;
  for(int i=1; i<=last; i++) {
    ans = max(ans, sum[i] - i + 1);
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
