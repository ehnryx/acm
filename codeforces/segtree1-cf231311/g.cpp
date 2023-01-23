#include <bits/stdc++.h>
using namespace std;

#include "../../lca/data_structure/segment_tree.h"

constexpr char nl = '\n';

struct Node {
  int offset;
  bool touched;
  Node() = default;
  pair<int,bool> get() const { return pair(offset, touched); }
  void put(int v) { offset = v; touched = true; }
  void push(Node& a, Node& b) {
    if(touched) {
      a.offset = b.offset = offset;
      a.touched = b.touched = true;
      touched = false;
    }
  }
  void pull(const Node&, const Node&) {}
};

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, m;
  cin >> n >> m;
  vector<int> a(n+1), b(n+1);
  for(int i=1; i<=n; i++) {
    cin >> a[i];
  }
  for(int i=1; i<=n; i++) {
    cin >> b[i];
  }

  segment_tree<Node, pair<int,bool>> st(n + 1);
  for(int i=0; i<m; i++) {
    int t;
    cin >> t;
    if(t == 1) {
      int x, y, k;
      cin >> x >> y >> k;
      st.update(y, y + k - 1, x - y);
    } else {
      int x;
      cin >> x;
      auto [offset, touched] = st.query_point(x);
      if (touched) {
        cout << a[x + offset] << nl;
      } else {
        cout << b[x] << nl;
      }
    }
  }

  return 0;
}
