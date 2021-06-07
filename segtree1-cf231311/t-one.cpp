#include <bits/stdc++.h>
using namespace std;

#include "../../lca/data_structure/segment_tree.h"

constexpr char nl = '\n';

constexpr int M = 26;
struct Node {
  valarray<int> cnt;
  int length;
  bool lazy;
  Node(char c = 0): cnt(M), length(1), lazy(false) {
    if(c) cnt[c - 'a'] = 1;
  }
  valarray<int> get() const { return cnt; }
  void put(int v = -1) {
    if(v == -1) cnt = 0;
    else cnt[v] = length;
    lazy = true;
  }
  void pull(const Node& a, const Node& b) {
    cnt = a.cnt + b.cnt;
    length = a.length + b.length;
  }
  void push(Node& a, Node& b) {
    if(lazy) {
      a.cnt = b.cnt = cnt / 2;
      a.lazy = b.lazy = true;
      lazy = false;
    }
  }
  static valarray<int> default_value() { assert(false); }
  static valarray<int> merge(const valarray<int>& a, const valarray<int>& b) {
    return a + b;
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

  segment_tree<Node, valarray<int>> st(s);
  while(m--) {
    int l, r, t;
    cin >> l >> r >> t;
    valarray<int> cnt = st.query(l, r);
    st.update(l, r);
    if(t == 1) {
      for(int j=0, i=l; j<M; j++) {
        st.update(i, i + cnt[j] - 1, j);
        i += cnt[j];
      }
    } else {
      for(int j=0, i=r; j<M; j++) {
        st.update(i - cnt[j] + 1, i, j);
        i -= cnt[j];
      }
    }
  }

  for(int i=1; i<st.length; i++) {
    st[i].push(st[2*i], st[2*i + 1]);
  }
  string ans;
  ans.reserve(n);
  for(int i=1; i<=n; i++) {
    const valarray<int>& leaf = st[i + st.length].cnt;
    ans.push_back('a' + (find(begin(leaf), end(leaf), 1) - begin(leaf)));
  }
  cout << ans << nl;

  return 0;
}
