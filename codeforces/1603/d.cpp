#include <bits/stdc++.h>
using namespace std;

#include "../../../lca/misc/fast_input.h"
//#include "../../../lca/data_structure/splay_tree.h"
#include "../../../lca/math/linear_sieve.h"

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int INF = 0x3f3f3f3f;
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());


int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
  fast_input cin;

  static constexpr int N = 1e5 + 1;
  linear_sieve<multiplicative_functions::totient> totient(N);
  vector<ll> f(N);
  for(int i=1; i<N; i++) {
    f[i] = totient[i] + f[i-1];
  }

  int T;
  cin >> T;
  while(T--) {
    int n, k;
    cin >> n >> k;

    int l = 1;
    int r = n;
    while(l < r) {
      int m = midpoint(l, r);
      int cnt = 0;
      for(int j=n; j>0; j/=(m+1)) {
        cnt++;
      }
      if(cnt > k) {
        l = m + 1;
      } else {
        r = m;
      }
    }

    vector<int> right(1);
    for(int i=1; i<k; i++) {
      right.push_back((right.back() + 1) * r);
    }

    ll ans = 0;
    for(int i=n; i>0; ) {
      assert(k > 0);
      int to = min(i / r, right[--k]);
      for(int j=to+1; j<=i; j++) {
        ans += f[i/j];
      }
      i = to;
    }
    cout << ans << nl;
  }

  return 0;
}
