#include <bits/stdc++.h>
using namespace std;

#include "../../lca/data_structure/segment_tree.h"

constexpr char nl = '\n';
using ll = long long;

struct Node {
  int value;
  Node() = default;
  void put(int v) { value = v; }
  int get() const { return value; }
  void push(Node&, Node&) {}
  void pull(const Node& a, const Node& b) { value = a.value + b.value; }
  static int default_value() { return 0; }
  static int merge(int a, int b) { return a + b; }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  cin >> n;
  map<int,int> moved;
  for(int i=0; i<n; i++) {
    int a, b;
    cin >> a >> b;
    if(!moved.count(a)) moved[a] = a;
    if(!moved.count(b)) moved[b] = b;
    swap(moved[a], moved[b]);
  }

  vector<pair<int,int>> values(begin(moved), end(moved));
  vector<pair<int,int>> order;
  for(int i=0; i<size(values); i++) {
    order.emplace_back(values[i].second, i);
  }
  sort(begin(order), end(order));

  ll ans = 0;
  segment_tree<Node, int> st(size(values));
  for(auto [_, i] : order) {
    ans += st.query(i, (int)size(values) - 1);
    st.update_point(i, 1);
  }
  for(int i=0; i<size(values); i++) {
    int j = lower_bound(begin(values), end(values), pair(values[i].second, 0)) - begin(values);
    ans += abs(values[i].first - values[i].second) + 1 - st.query(min(i, j), max(i, j));
  }
  cout << ans << nl;

  return 0;
}
