#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
//%:include "utility/output.h"

%:include "ds/segment_tree.h"
%:include "ds/segment_tree_nodes_min.h"

using ll = long long;
using ld = long double;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

using node = segment_tree_nodes::range_add_range_min<int>;

#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  int n;
  cin >> n;
  vector<int> b(n/2);
  for(int i=0; i<n/2; i++) {
    cin >> b[i];
  }
  auto sb = b;
  sort(begin(sb), end(sb));

  vector<int> h(n+1);
  for(int i=1, j=0; i<=n; i++) {
    if(j < n/2 and i == sb[j]) {
      h[i] = h[i-1] - 1;
      j++;
    } else {
      h[i] = h[i-1] + 1;
    }
    if(h[i] < 0) {
      return void(cout << -1 << nl);
    }
  }
  if(h[n] != 0) {
    return void(cout << -1 << nl);
  }

  segment_tree<node> st(h);
  vector<int> a(n);
  for(int i=0; i<n/2; i++) {
    a[2*i + 1] = b[i];
    st.update_range(b[i], n, 1);
    int j = st.search_right(0, n, 0) + 1;
    a[2*i] = j;
    st.update_range(j, n, -1);
  }

  for(int x : a) {
    cout << x << " ";
  }
  cout << nl;
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
