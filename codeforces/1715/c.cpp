#include <bits/stdc++.h>
using namespace std;

//%:include "utility/defines.h"
//%:include "utility/fast_input.h"
//%:include "utility/output.h"

%:include "ds/segment_tree.h"
%:include "ds/segment_tree_nodes_sum.h"

using ll = long long;
using ld = long double;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

using node = segment_node::range_add_range_sum<ll>;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#ifdef USING_FAST_INPUT
  fast_input cin;
#endif

  int n, m;
  cin >> n >> m;
  vector<int> a(n+1);
  for(int i=1; i<=n; i++) {
    cin >> a[i];
  }

  segment_tree<node> st(n+1);
  ll val = 0;
  for(int i=n; i>0; i--) {
    st.update_point(i, val + (n-i+1));
    if(a[i] != a[i-1]) {
      val += n-i+1;
    }
  }

  for(int i=0; i<m; i++) {
    int x, v;
    cin >> x >> v;
    // a[x] <- v
    if(1 < x) {
      int before = (a[x] != a[x-1]);
      int after = (v != a[x-1]);
      if(before != after) {
        st.update(1, x-1, (ll)(after - before) * (n-x+1));
      }
    }
    if(x < n) {
      int before = (a[x] != a[x+1]);
      int after = (v != a[x+1]);
      if(before != after) {
        st.update(1, x, (ll)(after - before) * (n-x));
      }
    }
    a[x] = v;
    //assert(st.query(1, n) == st[1].sum);
    //cout << st.query(1, n) << nl;
    cout << st[1].sum << nl;
  }

  return 0;
}
