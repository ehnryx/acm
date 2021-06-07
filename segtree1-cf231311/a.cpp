#include <bits/stdc++.h>
using namespace std;

#include "../../lca/data_structure/segment_tree.h"

constexpr char nl = '\n';

struct Node {
  int value;
  bool t;
  Node() = default;
  Node(const pair<int,int>& v): value(v.first), t(v.second) {}
  int get() const { return value; }
  void put(int v) {
    value = v;
  }
  void pull(Node& a, Node& b) {
    if((t = !a.t)) {
      value = a.value | b.value;
    } else {
      value = a.value ^ b.value;
    }
  }
  static int merge(int, int) { return 0; }
  static int default_value() { return 0; }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, m;
  cin >> n >> m;
  vector<pair<int,bool>> a(1<<n);
  for(int i=0; i<1<<n; i++) {
    cin >> a[i].first;
  }

  segment_tree<Node, int, false> st(a);
  for(int i=0; i<m; i++) {
    int x, v;
    cin >> x >> v;
    st.update(x-1, x-1, v);
    cout << st.query(0, (1<<n) - 1) << nl;
  }

  return 0;
}
