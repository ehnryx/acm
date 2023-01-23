#include <bits/stdc++.h>
using namespace std;

#include "../../lca/data_structure/segment_tree.h"

constexpr char nl = '\n';
using ll = long long;

struct Node {
  ll sum; int maxv, length;
  Node() = default;
  Node(int v): sum(v), maxv(v), length(1) {}
  void put(int v, bool reset = false) {
    if(reset) {
      sum = maxv = v;
    } else {
      assert(length == 1);
      sum %= v;
      maxv = sum;
    }
  }
  void pull(const Node& a, const Node& b) {
    sum = a.sum + b.sum;
    maxv = max(a.maxv, b.maxv);
    length = a.length + b.length;
  }
  ll get() const { return sum; }
  bool put_condition(int, bool reset = false) { return reset || length == 1; }
  bool break_condition(int v, bool reset = false) { return v > maxv; }
  static ll default_value() { assert(false); }
  static ll merge(ll a, ll b) { return a + b; }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, m;
  cin >> n >> m;
  vector<int> a(n+1);
  for(int i=1; i<=n; i++) {
    cin >> a[i];
  }
  segment_tree<Node, ll, false, true> st(a);

  for(int i=0; i<m; i++) {
    int t;
    cin >> t;
    if(t == 1) {
      int l, r;
      cin >> l >> r;
      cout << st.query(l, r) << nl;
    } else if(t == 2) {
      int l, r, x;
      cin >> l >> r >> x;
      st.update(l, r, x);
    } else {
      int k, x;
      cin >> k >> x;
      st.update_point(k, x, true);
    }
  }

  return 0;
}
