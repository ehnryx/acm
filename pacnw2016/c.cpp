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
  int n, k, r;
  cin >> n >> k >> r;
  vector<int> a(n+1);
  for(int i=0; i<k; i++) {
    int v;
    cin >> v;
    a[v] = 1;
  }
  int have = accumulate(begin(a), begin(a) + r, 0);
  int ans = 0;
  for(int i=r; i<=n; i++) {
    have += a[i] - a[i-r];
    if(have < 2) {
      have += 1 - a[i];
      ans += 1 - a[i];
      a[i] = 1;
    }
    if(have < 2) {
      have += 1 - a[i-1];
      ans += 1 - a[i-1];
      a[i-1] = 1;
    }
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
