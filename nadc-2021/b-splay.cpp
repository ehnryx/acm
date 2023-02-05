#include <bits/stdc++.h>
using namespace std;

%:include "string/suffix_tree.h"
%:include "data_structure/splay_tree.h"

//#define FILENAME sadcactus

constexpr char nl = '\n';

splay_tree<splay_node<int, void>> dfs(
    const vector<vector<pair<int, int>>>& put,
    const suffix_tree<basic_string, char>& st, int u, vector<int>& ans) {
  splay_tree<splay_node<int, void>> cur;
  for(auto [_, v] : st.nodes[u]) {
    splay_tree<splay_node<int, void>> child = dfs(put, st, v, ans);
    if (size(cur) < size(child)) {
      swap(cur, child);
    }
    for (int it : child) {
      cur.insert(it);
    }
  }
  if (st.is_leaf(u)) {
    cur.insert(st.strlen() - (st.depth(u) + st.length(u)) + 1);
  }
  for (auto [i, it] : put[u]) {
    if (it <= (int)size(cur)) {
      ans[i] = cur.at(it - 1)->key;
    }
  }
  return cur.dislodge();
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  string s;
  cin >> s;
  suffix_tree st(s);

  int m;
  cin >> m;
  vector<vector<pair<int, int>>> put(size(st.nodes));
  for(int i=0; i<m; i++) {
    int k;
    cin >> s >> k;
    int node = st.match(s).first;
    if (node != -1) {
      put[node].emplace_back(i, k);
    }
  }

  vector<int> ans(m, -1);
  dfs(put, st, st.root(), ans);
  for(int i=0; i<m; i++) {
    cout << ans[i] << nl;
  }

  return 0;
}

