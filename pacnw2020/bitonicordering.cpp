#include <bits/stdc++.h>
using namespace std;

#include "../../lca/data_structure/fenwick_tree.h"

const char nl = '\n';
using ll = long long;
using ld = long double;


int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  cin >> n;
  vector<int> a(n);
  vector<pair<int, int>> order;
  fenwick_tree<int> active(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    order.emplace_back(a[i], i);
    active.update_point(i, 1);
  }
  sort(begin(order), end(order));

  ll ans = 0;
  for (auto [v, i] : order) {
    active.update_point(i, -1);
    ans += min(active.query_range(0, i), active.query_range(i, n - 1));
  }
  cout << ans << nl;

  return 0;
}
