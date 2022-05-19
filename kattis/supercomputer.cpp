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

struct node final : segment_node::custom_update_range_sum<int> {
  int x;
  node() = default;
  void put() { x ^= 1; sum = x; }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#ifdef USING_FAST_INPUT
  fast_input cin;
#endif

  int n, k;
  cin >> n >> k;
  segment_tree<node> magic(n+1);
  for (int i=0; i<k; i++) {
    char t;
    cin >> t;
    if (t == 'F') {
      int id;
      cin >> id;
      magic.update_point(id);
    } else {
      int l, r;
      cin >> l >> r;
      cout << magic.query(l, r) << nl;
    }
  }

  return 0;
}
