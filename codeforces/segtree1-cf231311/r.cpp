#include <bits/stdc++.h>
using namespace std;

#include "../../lca/data_structure/segment_tree.h"

constexpr char nl = '\n';

struct Node {
  long long value, lazy;
  bool flag;
  Node() = default;
  Node(int v): value(v), lazy(0), flag(0) {}
  void put(int v) { value += v; lazy += v; flag = true; }
  long long get() const { return value; }
  void push(Node& a, Node& b) {
    if(flag) {
      a.put(lazy);
      b.put(lazy);
      lazy = 0;
      flag = false;
    }
  }
  void pull(const Node& a, const Node& b) { value = min(a.value, b.value); }
  static long long default_value() { assert(false); }
  static long long merge(long long a, long long b) { return min(a, b); }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  cin >> n;
  vector<int> a(n);
  for(int i=0; i<n; i++) {
    cin >> a[i];
  }
  segment_tree<Node, long long> st(a);

  int m;
  cin >> m;
  string s;
  getline(cin, s);
  for(int i=0; i<m; i++) {
    getline(cin, s);
    vector<int> vals;
    istringstream in(s);
    for(int v; in >> v; ) {
      vals.push_back(v);
    }
    if(size(vals) == 2) {
      if(vals[0] <= vals[1]) {
        cout << st.query(vals[0], vals[1]) << nl;
      } else {
        cout << min(st.query(vals[0], n-1), st.query(0, vals[1])) << nl;
      }
    } else {
      if(vals[0] <= vals[1]) {
        st.update(vals[0], vals[1], vals[2]);
      } else {
        st.update(vals[0], n-1, vals[2]);
        st.update(0, vals[1], vals[2]);
      }
    }
  }

  return 0;
}
