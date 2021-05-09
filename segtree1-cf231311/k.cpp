#include <bits/stdc++.h>
using namespace std;

#include "../../lca/data_structure/segment_tree.h"

constexpr char nl = '\n';

struct Node {
  int value;
  Node() = default;
  int get() const { return value; }
  void put(int v) { value = v; }
  void push(Node&, Node&) {}
  void pull(const Node& a, const Node& b) { value = max(a.value, b.value); }
  static void default_value() {}
  static void merge() {}
  bool contains(int k) { return value > k; }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  cin >> n;
  vector<tuple<string,int,int>> queries;
  vector<pair<int,int>> points;
  for(int i=0; i<n; i++) {
    string s;
    int x, y;
    cin >> s >> x >> y;
    queries.emplace_back(s, x, y);
    points.emplace_back(x, y);
  }
  sort(begin(points), end(points));

  segment_tree<Node, void> st(n);
  for(auto [s, x, y] : queries) {
    if(s == "add") {
      int i = lower_bound(begin(points), end(points), pair(x, y)) - begin(points);
      st.update_point(i, y);
    } else if(s == "remove") {
      int i = lower_bound(begin(points), end(points), pair(x, y)) - begin(points);
      st.update_point(i, 0);
    } else {
      int i = lower_bound(begin(points), end(points), pair(x+1, 0)) - begin(points);
      int j = st.search_left(i, n-1, y);
      if(j == -1) {
        cout << -1 << nl;
      } else {
        cout << points[j].first << " " << points[j].second << nl;
      }
    }
  }

  return 0;
}
