#include <bits/stdc++.h>
using namespace std;

#include "../../lca/data_structure/splay_tree.h"

const char nl = '\n';

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  int n;
  cin >> n;

  int cur = 0;
  splay_tree<splay_node<void, int>> parent;
  for (int i = 0; i <= n; i++) {
    parent.push_back(0);
  }

  for (int i=0; i<2*n; i++) {
    string s;
    int v;
    cin >> s >> v;
    if (s == "in") {
      parent.at(v)->value = cur;
      cur = v;
    } else {
      cur = parent.at(v)->value;
    }
  }

  for (int i=1; i<=n; i++) {
    if (parent.at(i)->value != 0) {
      cout << i << " " << parent.at(i)->value << nl;
    }
  }

  return 0;
}
