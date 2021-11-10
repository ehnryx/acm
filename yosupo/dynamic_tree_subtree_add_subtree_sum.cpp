#include <bits/stdc++.h>
using namespace std;

#include "../../lca/tree/euler_tour_tree.h"

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

struct data_t {
  ll val, sum, lazy;
  data_t(ll v=0): val(v), sum(v), lazy(0) {}
};

struct node final : euler_tour_node<node, data_t> {
  using euler_tour_node<node, data_t>::euler_tour_node;
  ll get() const { return value.sum; }
  void put(ll v) {
    if (ref()) {
      value.val += v;
    }
    value.sum += v * ref_cnt();
    value.lazy += v;
  }
  void push() {
    if(value.lazy) {
      if(left != nil) left->put(value.lazy);
      if(right != nil) right->put(value.lazy);
      value.lazy = 0;
    }
  }
  void pull() {
    euler_tour_node<node, data_t>::pull();
    value.sum = value.val + left->value.sum + right->value.sum;
  }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);

  int n, m;
  cin >> n >> m;

  euler_tour_tree<node> ett(n);

  for(int i=0; i<n; i++) {
    int v;
    cin >> v;
    ett.init(i, data_t(v));
  }

  for(int i=1; i<n; i++) {
    int a, b;
    cin >> a >> b;
    ett.link(a, b);
  }

  for(int i=0; i<m; i++) {
    int t;
    cin >> t;
    if(t == 0) {
      int u, v, w, x;
      cin >> u >> v >> w >> x;
      ett.cut(u, v);
      ett.link(w, x);
    } else if(t == 1) {
      int v, p, x;
      cin >> v >> p >> x;
      ett.update_subtree(v, p, x);
      //ett.cut(v, p);
      //ett.update_all(v, x);
      //ett.link(v, p);
    } else {
      int v, p;
      cin >> v >> p;
      cout << ett.query_subtree(v, p) << nl;
      //ett.cut(v, p);
      //cout << ett.query_all(v) << nl;
      //ett.link(v, p);
    }
  }

  return 0;
}
