#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
//%:include "utility/output.h"

%:include "ds/rmq_linear.h"

using ll = long long;
using ld = long double;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());


//#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  int n, q;
  cin >> n >> q;
  vector<ll> a(n+1);
  for(int i=1; i<=n; i++) {
    cin >> a[i];
  }
  range_minimum_query_linear rmq(a);

  while(q--) {
    ll v;
    int l, r;
    cin >> v >> l >> r;
    while(l <= r) {
      int lo = l;
      int hi = r+1;
      while(lo < hi) {
        int mid = (hi + lo) / 2;
        if(rmq.query(l, mid) <= v) {
          hi = mid;
        } else {
          lo = mid + 1;
        }
      }
      if(hi > r) break;
      v %= a[hi];
      l = hi + 1;
    }
    cout << v << nl;
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
