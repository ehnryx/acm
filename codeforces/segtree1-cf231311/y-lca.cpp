#pragma GCC optimize("O3")
#ifdef ONLINE_JUDGE
#pragma GCC target("sse4,avx2,tune=native")
#else
#pragma GCC target("sse4,avx2")
#endif

#include <bits/stdc++.h>
using namespace std;

#include "../../lca/data_structure/segment_tree.h"

constexpr char nl = '\n';

struct Node {
  static constexpr int neg = numeric_limits<int>::min();
  int value, cnt, lazy, index; bool leaf;
  Node(): value(neg), cnt(1), lazy(0), index(0), leaf(false) {}
  pair<int, int> get() const { return pair(value, cnt); }
  void put(int v) { value += v; lazy += v; }
  void put(int v, bool) { value = v; }
  void put(int, const function<void(int, int)>& func) {
    func(index, value);
    value = neg;
  }
  constexpr bool put_condition(int) const { return true; }
  constexpr bool break_condition(int) const { return value < 0; }
  constexpr bool put_condition(int, bool) const { return true; }
  constexpr bool break_condition(int, bool) const { return false; }
  bool put_condition(int, const function<void(int, int)>&) const { return leaf; }
  bool break_condition(int lb, const function<void(int, int)>&) const { return value <= lb; }
  void push(Node& a, Node& b) {
    if (lazy) {
      a.put(lazy);
      b.put(lazy);
      lazy = 0;
    }
  }
  const Node& pull(const Node& a, const Node& b) {
    value = max(a.value, b.value);
    cnt = (value == a.value) * a.cnt + (value == b.value) * b.cnt;
    return *this;
  }
  static pair<int, int> default_value() { assert(false); }
  static pair<int, int> merge(const pair<int, int>& a, const pair<int, int>& b) {
    int val = max(a.first, b.first);
    return pair(val, (val == a.first) * a.second + (val == b.first) * b.second);
  }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);

  static const int M = 1e4;
  vector<int> good;
  for (int i = 0; i <= M; i++) {
    string s = to_string(i);
    if (s.size() == count(begin(s), end(s), '4') + count(begin(s), end(s), '7')) {
      good.push_back(i);
    }
  }

  int n, m;
  cin >> n >> m;
  vector st(size(good), segment_tree<Node, pair<int, int>, true, true>(n + 1));
  function<void(int, int)> add_value = [&](int i, int v) {
    int j = lower_bound(begin(good), end(good), v) - begin(good);
    if (j < size(good)) st[j].update_point(i, v, true);
  };
  for (auto& tree : st) {
    for (int i = 0; i < tree.length; i++) {
      tree[i + tree.length].leaf = true;
      tree[i + tree.length].index = i;
    }
  }
  for (int i = 1; i <= n; i++) {
    int v;
    cin >> v;
    add_value(i, v);
  }

  while (m--) {
    string s;
    cin >> s;
    if (s == "count") {
      int l, r;
      cin >> l >> r;
      int ans = 0;
      for (int j = 0; j < (int)size(good); j++) {
        auto [value, cnt] = st[j].query(l, r);
        if (value == good[j]) {
          ans += cnt;
        }
      }
      cout << ans << nl;
    } else {
      int l, r, v;
      cin >> l >> r >> v;
      for (int j = (int)size(good) - 1; j >= 0; j--) {
        st[j].update(l, r, v);
        st[j].update(l, r, good[j], add_value);
      }
    }
  }

  return 0;
}
