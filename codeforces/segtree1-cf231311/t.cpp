#include <bits/stdc++.h>
using namespace std;

#include "../../lca/data_structure/segment_tree.h"

constexpr char nl = '\n';

struct Node {
  int value, length;
  bool lazy;
  Node(): value(0), length(1), lazy(false) {}
  int get() const { return value; }
  void put(int v) { value = v * length; lazy = true; }
  void pull(const Node& a, const Node& b) {
    value = a.value + b.value;
    length = a.length + b.length;
  }
  void push(Node& a, Node& b) {
    if(lazy) {
      a.value = b.value = value / 2;
      a.lazy = b.lazy = true;
      lazy = false;
    }
  }
  static int default_value() { assert(false); }
  static int merge(int a, int b) { return a + b; }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, m;
  cin >> n >> m;
  static const int M = 26;
  vector st(M, segment_tree<Node, int>(n+1, true));
  for(int i=1; i<=n; i++) {
    char c;
    cin >> c;
    st[c - 'a'].update_point(i, 1);
  }

  while(m--) {
    int l, r, t;
    cin >> l >> r >> t;
    vector<int> cnt(M);
    for(int j=0; j<M; j++) {
      cnt[j] = st[j].query(l, r);
      st[j].update(l, r, 0);
    }
    if(t == 1) {
      for(int j=0, i=l; j<M; j++) {
        st[j].update(i, i + cnt[j] - 1, 1);
        i += cnt[j];
      }
    } else {
      for(int j=0, i=r; j<M; j++) {
        st[j].update(i - cnt[j] + 1, i, 1);
        i -= cnt[j];
      }
    }
  }

  string ans;
  for(int i=1; i<=n; i++) {
    for(int j=0; j<M; j++) {
      if(st[j].query_point(i)) {
        ans.push_back('a' + j);
      }
    }
  }
  cout << ans << nl;
  assert(size(ans) == n);

  return 0;
}
