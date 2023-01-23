#include <bits/stdc++.h>
using namespace std;

constexpr char nl = '\n';

struct Segtree {
  static constexpr int neg = numeric_limits<int>::min();
  struct Node {
    int value, cnt, lazy;
    Node(): value(neg), cnt(1), lazy(0) {}
  };
  int n;
  vector<Node> st;
  Segtree(int len): n(1 << (len == 1 ? 0 : 32 - __builtin_clz(len - 1))), st(2 * n) {}
  void push(int i) {
    if (st[i].lazy) {
      st[2 * i].value += st[i].lazy;
      st[2 * i].lazy += st[i].lazy;
      st[2 * i + 1].value += st[i].lazy;
      st[2 * i + 1].lazy += st[i].lazy;
      st[i].lazy = 0;
    }
  }
  void pull(int i) {
    st[i].value = max(st[2 * i].value, st[2 * i + 1].value);
    st[i].cnt = 0;
    if (st[i].value == st[2 * i].value) st[i].cnt += st[2 * i].cnt;
    if (st[i].value == st[2 * i + 1].value) st[i].cnt += st[2 * i + 1].cnt;
  }
  void insert(int x, int v) {
    insert(x, 1, 0, n - 1, v);
  }
  void insert(int x, int i, int s, int e, int v) {
    if (s == e) {
      st[i].value = v;
      return;
    }
    push(i);
    int m = (s + e) / 2;
    if (x <= m) insert(x, 2 * i, s, m, v);
    else insert(x, 2 * i + 1, m + 1, e, v);
    pull(i);
  }
  void update(int l, int r, int v, int lb, const function<void(int, int)>& func) {
    return update(l, r, 1, 0, n - 1, v, lb, func);
  }
  void update(int l, int r, int i, int s, int e,
    int v, int lb, const function<void(int, int)>& func) {
    if (r < s || e < l || st[i].value < 0) return;
    if (l <= s && e <= r) {
      st[i].value += v;
      st[i].lazy += v;
      if (lb < st[i].value) {
        remove_big(i, s, e, lb, func);
      }
      return;
    }
    push(i);
    int m = (s + e) / 2;
    update(l, r, 2 * i, s, m, v, lb, func);
    update(l, r, 2 * i + 1, m + 1, e, v, lb, func);
    pull(i);
  }
  void remove_big(int i, int s, int e, int lb, const function<void(int, int)>& func) {
    if (st[i].value <= lb) return;
    if (s == e) {
      func(s, st[i].value);
      st[i].value = neg;
      return;
    }
    push(i);
    int m = (s + e) / 2;
    remove_big(2 * i, s, m, lb, func);
    remove_big(2 * i + 1, m + 1, e, lb, func);
    pull(i);
  }
  pair<int, int> query(int l, int r) {
    return query(l, r, 1, 0, n - 1);
  }
  pair<int, int> query(int l, int r, int i, int s, int e) {
    if (r < s || e < l) return pair(neg, 0);
    if (l <= s && e <= r) return pair(st[i].value, st[i].cnt);
    push(i);
    int m = (s + e) / 2;
    auto [lv, lc] = query(l, r, 2 * i, s, m);
    auto [rv, rc] = query(l, r, 2 * i + 1, m + 1, e);
    if (lv == rv) return pair(lv, lc + rc);
    else if(lv > rv) return pair(lv, lc);
    return pair(rv, rc);
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
  vector st(size(good), Segtree(n + 1));
  function<void(int, int)> add_value = [&](int i, int v) {
    int j = lower_bound(begin(good), end(good), v) - begin(good);
    if (j < size(good)) st[j].insert(i, v);
  };
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
        st[j].update(l, r, v, good[j], add_value);
      }
    }
  }

  return 0;
}
