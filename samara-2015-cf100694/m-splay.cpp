#include <bits/stdc++.h>
using namespace std;

#include "../../lca/data_structure/splay_tree.h"

const char nl = '\n';

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  int n, q;
  cin >> n >> q;

  splay_tree<splay_node<void, char>> why;
  while (why.push_back(0)->size <= q) {
    int a, b;
    cin >> a >> b;

    int sum = a+b;
    int base = n/sum;
    int add = (n - base*sum >= a);

    cout << 2*base + add << " ";
  }
  cout << nl;

  return 0;
}
