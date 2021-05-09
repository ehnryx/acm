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
  static int merge(int a, int b) { return plus<int>()(a, b); }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  long long m;
  cin >> n >> m;
  vector<int> a(n);
  map<int,int> remap;
  for(int i=0; i<n; i++) {
    cin >> a[i];
    remap[a[i]];
  }
  int rid = 0;
  for(auto& it : remap) {
    it.second = rid++;
  }
  for(int i=0; i<n; i++) {
    a[i] = remap[a[i]];
  }

  segment_tree<Node, int> left(n), right(n);
  left.update_point(a[0], 1);
  long long cur = 0;
  for(int i=n-1; i>0; i--) {
    cur += right.query(0, a[i] - 1);
    right.update_point(a[i], 1);
  }
  cur += right.query(0, a[0] - 1);

  long long ans = 0;
  for(int l=0, r=1; ; ) {
    while(r < n && cur > m) {
      cur -= left.query(a[r] + 1, n-1);
      cur -= right.query(0, a[r] - 1);
      right.update_point(a[r++], -1);
    }
    if(r == n) break;
    ans += n - r;
    if(++l == r) {
      cur -= left.query(a[r] + 1, n-1);
      cur -= right.query(0, a[r] - 1);
      right.update_point(a[r++], -1);
    }
    left.update_point(a[l], 1);
    cur += left.query(a[l] + 1, n-1);
    cur += right.query(0, a[l] - 1);
  }

  cout << ans << nl;

  return 0;
}
