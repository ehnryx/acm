#include <bits/stdc++.h>
using namespace std;

#include "../../../lca/string/suffix_tree.h"
#include "../../../lca/data_structure/range_minimum_query.h"
#include "../../../lca/data_structure/prefix_sum.h"

const char nl = '\n';
using ll = long long;

pair<ll, int> solve(const suffix_tree<int>& st,
                    const prefix_sum<ll>& sum,
                    const range_minimum_query<ll, greater<>>& rmq,
                    int u, ll path) {
  ll ans = numeric_limits<ll>::min();
  ll best = numeric_limits<ll>::min();
  if (st[u].left < st[u].right) {
    best = path + rmq.query(st[u].left, st[u].right) - sum[st[u].left - 1];
  }
  path += sum.query(st[u].left, st[u].right - 1);
  int leaves = st.is_leaf(u);
  for (auto [c, v] : st[u]) {
    auto [res, add] = solve(st, sum, rmq, v, path);
    ans = max(ans, res);
    leaves += add;
  }
  if (best != numeric_limits<ll>::min()) {
    ans = max(ans, best * leaves);
    assert(u != st.root());
  } else {
    assert(u == st.root() || st.is_leaf(u));
  }
  return pair(ans, leaves);
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int T;
  cin >> T;
  while (T--) {
    int n;
    cin >> n;
    vector<ll> a(n);
    map<int, int> remap;
    basic_string<int> s;
    for (int i = 0, rid = 1; i < n; i++) {
      cin >> a[i];
      if (!remap.count(a[i])) {
        remap[a[i]] = rid++;
      }
      s.push_back(remap[a[i]]);
    }

    suffix_tree st(s);
    prefix_sum sum(a);
    range_minimum_query<ll, greater<>> rmq(sum.data);
    cout << solve(st, sum, rmq, st.root(), 0).first << nl;
  }

  return 0;
}