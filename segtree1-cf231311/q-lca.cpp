#include <bits/stdc++.h>
using namespace std;

#include "../../lca/data_structure/segment_tree.h"
#include "../../lca/data_structure/dynamic_hull.h"

constexpr char nl = '\n';

struct Node {
  dynamic_hull<int> lc;
  Node() = default;
  Node(pair<int,int> line) { lc.insert(-line.first, -line.second); }
  int get(int x) const { return -lc.query(x); }
  void pull(const Node& l, const Node& r) {
    lc = l.lc;
    for (auto [m, b, _] : r.lc) lc.insert(m, b);
  } // no updates
  static int default_value() { assert(false); }
  static int merge(int a, int b) { return min(a, b); }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  cin >> n;
  vector<int> a(n+1), s(n+1);
  for(int i=1; i<=n; i++) {
    cin >> a[i];
  }
  partial_sum(begin(a), end(a), begin(s));
  vector<pair<int,int>> lines(n+1);
  for(int i=1; i<=n; i++) {
    lines[i] = pair(-a[i], i*a[i] - s[i-1]);
  }
  segment_tree<Node, int, false> st(lines);

  int m;
  cin >> m;
  for(int i=0; i<m; i++) {
    int x, y;
    cin >> x >> y;
    int left = y - x + 1;
    int right = y;
    cout << s[right] + st.query(left, right, left) << nl;
  }

  return 0;
}
