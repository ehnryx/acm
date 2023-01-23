#include <bits/stdc++.h>
using namespace std;

#include "../../lca/data_structure/segment_tree.h"

constexpr char nl = '\n';

struct Node {
  int inc, dec, fours, sevens;
  bool flag;
  Node() = default;
  Node(char c): fours(c == '4'), sevens(c == '7'), flag(false) {
    inc = dec = fours + sevens;
  }
  void put() {
    swap(fours, sevens);
    swap(inc, dec);
    flag ^= 1;
  }
  void push(Node& l, Node& r) {
    if (flag) {
      l.put();
      r.put();
      flag = false;
    }
  }
  void pull(const Node& l, const Node& r) {
    inc = max(l.inc, r.inc);
    inc = max(inc, l.inc + r.sevens);
    inc = max(inc, l.fours + r.inc);
    dec = max(l.dec, r.dec);
    dec = max(dec, l.sevens + r.dec);
    dec = max(dec, l.dec + r.fours);
    fours = l.fours + r.fours;
    sevens = l.sevens + r.sevens;
  }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, m;
  cin >> n >> m;
  vector<char> s(n+1);
  for(int i=1; i<=n; i++) {
    cin >> s[i];
  }

  segment_tree<Node, void> st(s);
  while(m--) {
    string t;
    cin >> t;
    if(t == "count") {
      cout << st[1].inc << nl;
    } else {
      int l, r;
      cin >> l >> r;
      st.update(l, r);
    }
  }

  return 0;
}
