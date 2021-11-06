#include <bits/stdc++.h>
using namespace std;

#include "../../lca/data_structure/link_cut_tree.h"

//#define FILENAME sadcactus

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int INF = 0x3f3f3f3f;
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

struct data_t {
  ll val, sum;
  data_t(): val(0), sum(0) {}
};

struct node final : link_cut_node<node, data_t> {
  using link_cut_node<node, data_t>::link_cut_node;
  ll get() const { return value.sum; }
  void pull() {
    value.sum = value.val + left->value.sum + right->value.sum;
  }
};

// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#if defined(ONLINE_JUDGE) && defined(FILENAME)
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif

  int n, m;
  cin >> n >> m;

  link_cut_tree<node> lct(n);
  for(int i=0; i<n; i++) {
    int a;
    cin >> a;
    lct[i].value.val = lct[i].value.sum = a;
  }

  for(int i=1; i<n; i++) {
    int a, b;
    cin >> a >> b;
    lct.link(a, b);
  }

  while(m--) {
    int t;
    cin >> t;
    if(t == 0) {
      int u, v, w, x;
      cin >> u >> v >> w >> x;
      lct.cut(u, v);
      lct.link(w, x);
    } else if(t == 1) {
      int u, x;
      cin >> u >> x;
      lct.splay(&lct[u]);
      lct[u].value.val += x;
      lct[u].value.sum += x;
    } else if(t == 2) {
      int u, v;
      cin >> u >> v;
      cout << lct.query_path(u, v) << nl;
    } else {
      assert(false);
    }
  }

  return 0;
}
