#include <bits/stdc++.h>
using namespace std;

#include "../../lca/graph/min_cost_flow.h"

const char nl = '\n';
using ll = long long;
using ld = long double;


int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  cin >> n;
  min_cost_flow<ll> minv(2 * n + 2), maxv(2 * n + 2);
  const int source = 2 * n;
  const int sink = 2 * n + 1;

  vector<int> skill(n);
  for (int i = 0; i < n; i++) {
    int g;
    cin >> skill[i] >> g;
    minv.add_edge(source, i, g - 1, 0);
    minv.add_edge(i + n, sink, 1, 0);
    maxv.add_edge(source, i, g - 1, 0);
    maxv.add_edge(i + n, sink, 1, 0);
  }
  int winner = max_element(begin(skill), end(skill)) - begin(skill);
  minv.add_edge(source, winner + n, 1, 0);
  minv.add_edge(source, winner, 1, 0);
  maxv.add_edge(source, winner + n, 1, 0);
  maxv.add_edge(source, winner, 1, 0);

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (skill[i] > skill[j]) {
        minv.add_edge(i, j + n, 1, skill[i] ^ skill[j]);
        maxv.add_edge(i, j + n, 1, -(skill[i] ^ skill[j]));
      }
    }
  }

  ll min_cost = minv.flow(source, sink).second;
  ll max_cost = -maxv.flow(source, sink).second;
  cout << min_cost << " " << max_cost << nl;

  return 0;
}
