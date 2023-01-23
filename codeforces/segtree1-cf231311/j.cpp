#include <bits/stdc++.h>
using namespace std;

#include "../../lca/data_structure/segment_tree.h"

constexpr char nl = '\n';

struct Node {
  int value, sum;
  Node() = default;
  int get() const { return value; }
  void put(int v) {
    value += v;
    sum += v;
  }
  void push(Node&, Node&) {}
  void pull(const Node& a, const Node& b) {
    sum = a.sum + b.sum;
    value = min(a.value, a.sum + b.value);
  }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, m, h;
  cin >> n >> m >> h;
  vector<int> a(n), b(m);
  map<int,int> remap;
  for(int i=0; i<m; i++) {
    cin >> b[i];
    remap[b[i]];
  }
  for(int i=0; i<n; i++) {
    cin >> a[i];
    remap[a[i] = h - a[i]];
  }
  int rid = 0;
  for(auto& it : remap) {
    it.second = rid++;
  }
  for(int& v : a) v = remap[v];
  for(int& v : b) v = remap[v];

  segment_tree<Node,int> st(rid);
  for(int i=0; i<m; i++) {
    st.update_point(a[i], 1);
    st.update_point(b[i], -1);
  }
  int ans = (st[1].value >= 0);
  for(int i=m; i<n; i++) {
    st.update_point(a[i], 1);
    st.update_point(a[i-m], -1);
    ans += (st[1].value >= 0);
  }
  cout << ans << nl;

  return 0;
}
