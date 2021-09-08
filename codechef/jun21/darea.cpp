#include <bits/stdc++.h>
using namespace std;

#include "../../../lca/data_structure/range_minimum_query.h"

const char nl = '\n';
using ll = long long;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;
  while (T--) {
    int n;
    cin >> n;
    vector<pair<int, int>> v;
    for (int i = 0; i < n; i++) {
      int x, y;
      cin >> x >> y;
      v.emplace_back(x, y);
    }

    if (n == 1) {
      cout << 0 << nl;
      continue;
    }

    ll ans = numeric_limits<ll>::max();

    sort(begin(v), end(v));
    vector<int> ys;
    transform(begin(v), end(v), back_inserter(ys),
              [](const pair<int, int>& it) { return it.second; });
    range_minimum_query<int> minv(ys);
    range_minimum_query<int, greater<int>> maxv(ys);
    for (int i = 1; i < n; i++) {
      ll left = (ll)(v[i - 1].first - v[0].first) * (maxv.query(0, i) - minv.query(0, i));
      ll right = (ll)(v[n - 1].first - v[i].first) * (maxv.query(i, n) - minv.query(i, n));
      ans = min(ans, left + right);
    }

    sort(begin(v), end(v),
         [](const auto& it, const auto& jt) { return it.second < jt.second; });
    transform(begin(v), end(v), begin(ys),
              [](const pair<int, int>& it) { return it.first; });
    minv = range_minimum_query(ys);
    maxv = range_minimum_query<int, greater<int>>(ys);
    for(int i=1; i<n; i++) {
      ll left = (ll)(v[i - 1].second - v[0].second) * (maxv.query(0, i) - minv.query(0, i));
      ll right = (ll)(v[n - 1].second - v[i].second) * (maxv.query(i, n) - minv.query(i, n));
      ans = min(ans, left + right);
    }

    cout << ans << nl;
  }

  return 0;
}