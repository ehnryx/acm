#include <bits/stdc++.h>
using namespace std;

#include "../../lca/data_structure/segment_tree.h"

constexpr char nl = '\n';

struct Node {
  int value;
  Node(int v = 0): value(v) {}
  int get() const { return value; }
  void put(int v) { value = v; }
  void push(Node&, Node&) {}
  void pull(const Node& a, const Node& b) { value = a.value + b.value; }
  bool contains(int& k) const {
    if(k <= value) return true;
    k -= value;
    return false;
  }
  static int default_value() { return 0; }
  static int merge(int a, int b) { return a + b; }
};

vector<int> generate(int n) {
  vector<pair<int,int>> order;
  for(int i=0; i<n; i++) {
    int v;
    cin >> v;
    order.emplace_back(v, i);
  }
  sort(begin(order), end(order));

  segment_tree<Node, int> st(n);
  vector<int> res(n);
  for(auto [_, i] : order) {
    res[n-1-i] = st.query(i, n-1);
    st.update_point(i, 1);
  }
  return res;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  cin >> n;
  vector<int> a = generate(n);
  vector<int> b = generate(n);
  for(int i=0; i<n; i++) {
    a[i] += b[i];
    if(a[i] >= i+1) {
      if(i+1 < n) a[i+1] += a[i] / (i+1);
      a[i] %= (i+1);
    }
  }

  //segment_tree<Node, int> st(n, true);
  segment_tree<Node, int> st(vector<int>(n, 1));
  vector<int> ans;
  ans.reserve(n);
  for(int i=n-1; i>=0; i--) {
    int j = st.search_left(0, n-1, a[i] + 1);
    st.update_point(j, 0);
    ans.push_back(j);
  }

  for(int i=0; i<n; i++) {
    cout << ans[i] << " ";
  }
  cout << nl;

  return 0;
}
