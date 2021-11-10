#include <bits/stdc++.h>
using namespace std;

#include "../../lca/tree/link_cut_tree.h"
#include "../../lca/tree/euler_tour_tree.h"

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

struct data_t {
  int v, lazy, mul;
  data_t(int _v=0, int _z=0, int _m=0): v(_v), lazy(_z), mul(_m) {}
};

struct node final : euler_tour_node<node, data_t> {
  using euler_tour_node<node, data_t>::euler_tour_node;
  void put(int v) {
    value.v += v;
    value.lazy += v;
  }
  void push() {
    if(value.lazy) {
      if(left != nil) left->put(value.lazy);
      if(right != nil) right->put(value.lazy);
      value.lazy = 0;
    }
  }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);

  int n;
  cin >> n;

  link_cut_tree<simple_link_cut_node> lct(n+1);
  euler_tour_tree<node> ett(n+1);
  vector<int> parent(n+1);
  vector<bool> removed(n+1);
  vector<vector<int>> adj(n+1);

  for(int i=1; i<n; i++) {
    int a, b;
    cin >> a >> b;
    lct.link(a, b);
    ett.link(a, b);
    adj[a].push_back(b);
    adj[b].push_back(a);
  }

  lct.reroot(1);
  function<void(int, int, int)> dfs = [&](int u, int p, int d) {
    parent[u] = p;
    ett[u].value.mul = d;
    for(int v : adj[u]) {
      if(v == p) continue;
      dfs(v, u, -d);
    }
  };
  dfs(1, 0, 1);

  int q;
  cin >> q;
  while (q--) {
    int t;
    cin >> t;
    if(t == 1) {
      int x;
      cin >> x;
      removed[x] = true;
      if (parent[x]) {
        ett.cut(x, parent[x]);
        lct.cut(x, parent[x]);
      }
    } else if(t == 2) {
      int x;
      cin >> x;
      removed[x] = false;
      if (parent[x]) {
        ett.link(x, parent[x]);
        lct.link(parent[x], x);
      }
    } else {
      int x, a;
      cin >> x >> a;
      int r = lct.find_root(x);
      int new_r = -1;
      if (removed[r]) {
        new_r = lct.step_down_towards(r, x);
        lct.cut(new_r, r);
        ett.cut(new_r, r);
      }
      cout << a * ett.size(x) << nl;
      ett.update_all(x, a * ett[x].value.mul);
      if (removed[r]) {
        lct.link(r, new_r);
        ett.link(r, new_r);
      }
    }
  }

  ll ans = 0;
  for (int i=1; i<=n; i++) {
    int cur = ett.splay(ett.ptr(i))->value.v * ett[i].value.mul;
    ans += (cur % 360 + 360) % 360;
  }
  cout << ans << nl;

  return 0;
}
