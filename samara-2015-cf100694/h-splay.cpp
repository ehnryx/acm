#include <bits/stdc++.h>
using namespace std;

#include "../../lca/data_structure/splay_tree.h"

const char nl = '\n';

struct node_max final : splay_node_base<node_max, void, pair<int, int>> {
  using splay_node_base<node_max, void, pair<int, int>>::splay_node_base;
  int get() const { return value.second; }
  void pull() {
    value.second = max(value.first, max(left->value.second, right->value.second));
  }
};

struct node_sum final : splay_node_base<node_sum, void, pair<int, int>> {
  using splay_node_base<node_sum, void, pair<int, int>>::splay_node_base;
  int get() const { return value.second; }
  void pull() {
    value.second = value.first + left->value.second + right->value.second;
  }
};

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);

  int n;
  cin >> n;

  splay_tree<node_max> m_tree(n);
  for (int i=0; i<n; i++) {
    int a;
    cin >> a;
    m_tree.at(i)->value.first = a;
    m_tree.at(i)->pull();
  }
  for (int i=0; i<n; i++) {
    int a;
    cin >> a;
  }

  int k;
  cin >> k;

  splay_tree<node_sum> sum_tree(k);
  for (int i=0; i<k; i++) {
    int a;
    cin >> a;
    sum_tree.at(i)->value.first = a;
    sum_tree.at(i)->pull();
  }

  int m = m_tree.query_range(0, n-1);
  int sum = sum_tree.query_range(0, k-1);
  cout << m*k+sum << nl;

  return 0;
}
