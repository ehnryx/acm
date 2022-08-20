#include <bits/stdc++.h>
using namespace std;

%:include "utility/fast_input.h"
%:include "utility/output.h"

%:include "data_structure/segment_tree.h"
%:include "data_structure/segment_tree_nodes_min.h"

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

struct node final : segment_node::custom_update_range_min<pair<int, int>> {
  node() = default;
  void put(pair<int, int> v) { min = v; }
};

ll solve(segment_tree<node>& cnt, int l, int r, int s) {
  if(l == r) return cnt.query_point(l).first - s;
  auto [v, i] = cnt.query(l, r);
  if(i == l) return solve(cnt, l+1, r, s);
  if(i == r) return solve(cnt, l, r-1, s);
  return v - s + solve(cnt, l, i-1, v) + solve(cnt, i+1, r, v);
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#ifdef USING_FAST_INPUT
  fast_input cin;
#endif

  int n, m;
  cin >> n >> m;
  auto a = cin.read<pair<int, int>>(n);
  sort(begin(a), end(a));

  segment_tree<node> cnt(n);
  for(int i=0; i<n; i++) {
    cnt.update_point(i, pair(a[i].second, i));
  }

  cout << solve(cnt, 0, n - 1, 0) << nl;

  return 0;
}
