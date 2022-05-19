#include <bits/stdc++.h>
using namespace std;

%:include "utility/fast_input.h"
%:include "ds/fenwick_tree.h"

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());


int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#ifdef USING_FAST_INPUT
  fast_input cin;
#endif

  int n;
  cin >> n;
  vector<int> idx(n+1);
  for(int i=1; i<=n; i++) {
    int v;
    cin >> v;
    idx[v] = i;
  }

  fenwick_tree<int> done(n+1);
  int left = 1;
  int right = n;
  int ans = 0;
  for(int i=1; i<=n; i++) {
    if(i%2) {
      ans = idx[left]-1 - done.query(1, idx[left]);
      done.insert(idx[left++]);
    } else {
      ans = n-idx[right] - done.query(idx[right], n);
      done.insert(idx[right--]);
    }
    cout << ans << nl;
  }

  return 0;
}
