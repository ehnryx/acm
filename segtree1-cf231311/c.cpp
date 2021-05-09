#include <bits/stdc++.h>
using namespace std;

#define USE_NO_PUSH
#include "../../lca/data_structure/segment_tree.h"

constexpr char nl = '\n';

struct Node {
  vector<int> all;
  Node() = default;
  Node(int v): all(1, v) {}
  int get(int ub) const {
    return (int)(lower_bound(begin(all), end(all), ub) - begin(all));
  }
  void pull(Node& a, Node& b) {
    all.resize(size(a.all) + size(b.all));
    std::merge(
        begin(a.all), end(a.all),
        begin(b.all), end(b.all),
        begin(all));
  }
  static int default_value() { return 0; }
  static int merge(int a, int b) { return a + b; }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  cin >> n;
  vector<int> a(n);
  for(int i=0; i<n; i++) {
    cin >> a[i];
  }

  map<int,int> cnt;
  vector<int> suffix(n);
  for(int i=n-1; i>=0; i--) {
    suffix[i] = ++cnt[a[i]];
  }
  segment_tree<Node, int> st(suffix);

  long long ans = 0;
  cnt.clear();
  for(int i=0; i<n; i++) {
    int left = ++cnt[a[i]];
    ans += st.query(i+1, n-1, left);
  }
  cout << ans << nl;

  return 0;
}
