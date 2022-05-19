#include <bits/stdc++.h>
using namespace std;

%:include "utility/fast_input.h"
%:include "ds/segment_tree.h"
%:include "ds/segment_tree_nodes.h"

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

/*
struct node {
  int val = 0;
  void put(int v) { val = v; }
  int get() const { return val; }
  void pull(const node& l, const node& r) {
    val = l.val + r.val;
  }
  static int merge(int a, int b) { return a + b; }
};
*/

using node = segment_node::range_assign_range_sum<int>;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#ifdef USING_FAST_INPUT
  fast_input cin;
#endif

  int T;
  cin >> T;
  while (T--) {
    int n, m;
    cin >> n >> m;
    segment_tree<node> segt(n + m + 1);
    vector<int> pos(n+1);
    for (int i=1; i<=n; i++) {
      segt.update_point(n-i, 1);
      pos[i] = n-i;
    }

    for (int i=0, top=n; i<m; i++) {
      int a;
      cin >> a;
      cout << segt.query(pos[a]+1, top) << " ";
      segt.update_point(pos[a], 0);
      segt.update_point(top, 1);
      pos[a] = top++;
    }
    cout << nl;
  }

  return 0;
}
