#include <bits/stdc++.h>
using namespace std;

#include "../../lca/data_structure/segment_tree.h"

constexpr char nl = '\n';

struct Node {
  int value, lazy;
  Node() = default;
  Node(int v): value(v), lazy(0) {}
  int get() const { return value; }
  void put(int v) { value = lazy = v; }
  void push(Node& a, Node& b) {
    if(lazy) {
      a.put(lazy);
      b.put(lazy);
      lazy = 0;
    }
  }
  void pull(Node&, Node&) {}
};

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, m;
  cin >> n >> m;
  segment_tree<Node, int> st(n + 1);

  vector<tuple<int,int,int>> queries;
  queries.reserve(m);
  for(int i=0; i<m; i++) {
    int l, r, x;
    cin >> l >> r >> x;
    queries.emplace_back(l, r, x);
  }
  reverse(begin(queries), end(queries));

  for(auto [l, r, x] : queries) {
    st.update(l, x-1, x);
    st.update(x+1, r, x);
  }

  for(int i=1; i<=n; i++) {
    cout << st.query_point(i) << " ";
  }
  cout << nl;

  return 0;
}
