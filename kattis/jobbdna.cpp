#include <bits/stdc++.h>
using namespace std;

#include "../../lca/string/suffix_tree.h"

constexpr char nl = '\n';

vector<int> get_leaves(const suffix_tree<char>& st, int u) {
  if (st.is_leaf(u)) return { u };
  vector<int> leaves;
  for (auto [_, v] : st[u]) {
    vector<int> subtree = get_leaves(st, v);
    if (size(leaves) < size(subtree)) swap(leaves, subtree);
    leaves.insert(end(leaves), begin(subtree), end(subtree));
  }
  return leaves;
}

pair<int, int> solve(const suffix_tree<char>& st, int n, int len, int u) {
  if (st.depth(u) + st.length(u) < len) {
    int start = -1, cnt = -1;
    for (auto [_, v] : st[u]) {
      auto [s, c] = solve(st, n, len, v);
      if (c > cnt) {
        cnt = c;
        start = s;
      }
    }
    return pair(start, cnt);
  }

  vector<int> leaves = get_leaves(st, u);
  sort(begin(leaves), end(leaves));
  int m = lower_bound(begin(leaves), end(leaves), n) - begin(leaves);

  vector<int> to(m);
  for (int i = 0, j = 0; i < size(leaves); i++) {
    while (j < i && leaves[i] - leaves[j + 1] >= len) {
      j++;
    }
    if (leaves[j] >= n) break;
    if (leaves[i] - leaves[j] >= len) {
      int id = i < m ? i : i - m;
      to[id] = j;
    }
  }

  int cnt = 0;
  vector<int> dist(m, -1);
  for (int i = 0; i < m; i++) {
    if (dist[i] != -1) continue;
    dist[i] = 0;
    int t = i;
    while (dist[to[t]] == -1) {
      dist[to[t]] = dist[t] + 1;
      t = to[t];
    }
    cnt = max(cnt, dist[t] + 1 - dist[to[t]]);
  }
  return pair(leaves.front(), cnt);
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, m;
  cin >> n >> m;
  string s;
  cin >> s;
  suffix_tree st(s + s);
  auto [start, cnt] = solve(st, n, m, st.root());
  cout << st.t.substr(start, m) << nl;
  cerr << "count: " << cnt << nl;

  return 0;
}
