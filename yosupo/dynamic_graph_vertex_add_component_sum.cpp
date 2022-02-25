#include <bits/stdc++.h>
using namespace std;

#include "../../lca/graph/dynamic_connectivity.h"

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

struct data_t {
  ll val, sum;
  data_t(ll v=0): val(v), sum(v) {}
};

struct node final : dynamic_connectivity_node<node, data_t> {
  using dynamic_connectivity_node<node, data_t>::dynamic_connectivity_node;
  ll get() const { return value.sum; }
  void put(ll v) {
    value.val += v;
    value.sum += v;
  }
  void pull() {
    dynamic_connectivity_node<node, data_t>::pull();
    value.sum = value.val + left->value.sum + right->value.sum;
  }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);

  int n, m;
  cin >> n >> m;

  dynamic_connectivity<node/*, false*/> graph(n);

  for(int i=0; i<n; i++) {
    int v;
    cin >> v;
    graph.init(i, data_t(v));
  }

  for (int i=0; i<m; i++) {
    int t;
    cin >> t;
    if(t == 0) {
      int u, v;
      cin >> u >> v;
      graph.link(u, v);
    } else if(t == 1) {
      int u, v;
      cin >> u >> v;
      graph.cut(u, v);
    } else if(t == 2) {
      int v, x;
      cin >> v >> x;
      graph.splay(v)->put(x);
    } else if(t == 3) {
      int v;
      cin >> v;
      cout << graph.query_component(v) << nl;
    } else {
      assert(false);
    }
  }

  return 0;
}
