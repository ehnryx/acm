#include <bits/stdc++.h>
using namespace std;

#include "../../lca/data_structure/segment_tree.h"

constexpr char nl = '\n';

struct Node {
  int res, length, left, right;
  Node() = default;
  Node(char c): res(0), length(1), left(c == ')'), right(c == '(') {}
  Node get() const { return *this; }
  void push(Node&, Node&) {}
  Node& pull(const Node& a, const Node& b) {
    int match = min(a.right, b.left);
    res = a.res + b.res + 2 * match;
    length = a.length + b.length;
    left = a.left + b.left - match;
    right = a.right + b.right - match;
    return *this;
  }
  static Node default_value() { return Node(); }
  static Node merge(const Node& a, const Node& b) { return Node().pull(a, b); }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);

  string s;
  cin >> s;
  segment_tree<Node, Node> st(vector<char>(begin(s), end(s)));

  int n;
  cin >> n;
  for(int i=0; i<n; i++) {
    int l, r;
    cin >> l >> r;
    cout << st.query(l-1, r-1).res << nl;
  }

  return 0;
}
