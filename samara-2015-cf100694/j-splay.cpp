#include <bits/stdc++.h>
using namespace std;

#include "../../lca/data_structure/splay_tree.h"

const char nl = '\n';

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  int n, m, k;
  cin >> n >> m >> k;

  splay_tree<splay_node<int, int>> remap;

  splay_tree<splay_node<void, int>> choice(n+1);
  for (int i=1; i<=n; i++) {
    cin >> choice[i];
  }

  splay_tree<splay_node<int, void>> p;
  for (int i=0; i<m; i++) {
    int a;
    cin >> a;
    p.insert(a);
  }

  for (int i=0; i<m; i++) {
    remap.insert(p[i], i);
  }

  for (int i=1; i<=n; i++) {
    choice[i] = remap.find(choice[i])->value;
  }

  splay_tree<splay_node<void, pair<int, int>>> cts;
  int start = 1;
  for (int i=2; i<=n; i++) {
    if (choice[i]-choice[start] != i-start || i-start == k) {
      cts.push_back(pair(start, i-1));
      start = i;
    }
  }
  cts.push_back(pair(start, n));

  cout << cts.size() << nl;
  for (const pair<int, int>& it : cts) {
    cout << it.second-it.first+1 << " ";
    for (int i=it.first; i <= it.second; i++) {
      cout << i << " ";
    }
    cout << nl;
  }

  return 0;
}
