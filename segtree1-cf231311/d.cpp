#include <bits/stdc++.h>
using namespace std;

#define USE_NO_PUSH
#include "../../lca/data_structure/segment_tree.h"

constexpr char nl = '\n';

struct Node {
  int sum;
  Node() = default;
  void put(int v) { sum = v; }
  int get() const { return sum; }
  void pull(Node& a, Node& b) { sum = a.sum + b.sum; }
  static int default_value() { return 0; }
  static int merge(int a, int b) { return a + b; }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  cin >> n;
  vector<pair<int,int>> order;
  for(int i=0; i<n; i++) {
    int a;
    cin >> a;
    order.emplace_back(a, i);
  }
  sort(begin(order), end(order));

  vector<int> smaller(n);
  segment_tree<Node, int> st(n), lt(n);
  for(auto [_, i] : order) {
    smaller[i] = st.query(i+1, n-1);
    st.update_point(i, 1);
  }
  reverse(begin(order), end(order));
  long long ans = 0;
  for(auto [_, i] : order) {
    ans += (long long)smaller[i] * lt.query(0, i-1);
    lt.update_point(i, 1);
  }
  cout << ans << nl;

  return 0;
}
