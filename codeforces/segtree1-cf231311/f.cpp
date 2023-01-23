#include <bits/stdc++.h>
using namespace std;

#include "../../lca/data_structure/segment_tree.h"

constexpr char nl = '\n';

struct Node {
  int value, count;
  Node() = default;
  Node(int v): value(v), count(1) {}
  Node get() const { return *this; }
  Node& pull(const Node& a, const Node& b) {
    value = gcd(a.value, b.value);
    count = (value == a.value) * a.count + (value == b.value) * b.count;
    return *this;
  }
  static Node default_value() { assert(false); }
  static Node merge(const Node& a, const Node& b) { return Node().pull(a, b); }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  cin >> n;
  vector<int> a(n + 1);
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  segment_tree<Node, Node, false> st(a);

  int m;
  cin >> m;
  for (int i = 0; i < m; i++) {
    int l, r;
    cin >> l >> r;
    cout << r - l + 1 - st.query(l, r).count << nl;
  }

  return 0;
}
