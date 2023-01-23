#include <bits/stdc++.h>
using namespace std;

#include "../../lca/data_structure/segment_tree.h"

constexpr char nl = '\n';

struct Node {
  int value;
  Node() = default;
  int get() const { return value; }
  void put(int v) { value += v; }
  void push(Node&, Node&) {}
  void pull(const Node& a, const Node& b) { value = a.value + b.value; }
  static int default_value() { return 0; }
  static int merge(int a, int b) { return a + b; }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  cin >> n;
  vector<int> a(n+1);
  for(int i=1; i<=n; i++) {
    cin >> a[i];
  }

  int m;
  cin >> m;
  vector<int> ans(m);
  vector<tuple<int,int,int>> queries;
  for(int i=0; i<m; i++) {
    int l, r;
    cin >> l >> r;
    queries.emplace_back(l, r, i);
  }
  sort(begin(queries), end(queries), greater<>());

  int len = *max_element(begin(a), end(a)) + 1;
  vector<int> last(len), last2(len), diff(len), rb(len, n + 1);
  segment_tree<Node,int> st(n+2), have(n+2);
  int pos = n;
  for(auto [l, r, i] : queries) {
    while(pos >= l) {
      if(!last[a[pos]]) {
        have.update_point(pos, 1);
        st.update_point(last[a[pos]] = pos, 1);
      } else if(!diff[a[pos]] || last[a[pos]] - pos == diff[a[pos]]) {
        diff[a[pos]] = last[a[pos]] - pos;
        have.update_point(pos, 1);
        have.update_point(last[a[pos]], -1);
        last2[a[pos]] = last[a[pos]];
        st.update_point(last[a[pos]], -1);
        st.update_point(last[a[pos]] = pos, 1);
      } else {
        diff[a[pos]] = last[a[pos]] - pos;
        have.update_point(pos, 1);
        have.update_point(last[a[pos]], -1);
        st.update_point(rb[a[pos]], 1);
        st.update_point(rb[a[pos]] = last2[a[pos]], -1);
        last2[a[pos]] = last[a[pos]];
        st.update_point(last[a[pos]], -1);
        st.update_point(last[a[pos]] = pos, 1);
      }
      pos--;
    }
    bool good = (st.query(l, r) > 0);
    ans[i] = have.query(l, r) + !good;
  }

  for(int i=0; i<m; i++) {
    cout << ans[i] << nl;
  }

  return 0;
}
