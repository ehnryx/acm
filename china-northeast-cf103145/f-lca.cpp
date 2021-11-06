#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include "../../lca/data_structure/splay_tree.h"
#include "../../lca/misc/fast_input.h"

//#define FILENAME sadcactus

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
template <typename T>
using ordered_set = __gnu_pbds::tree<T,
      __gnu_pbds::null_type,
      less<T>,
      __gnu_pbds::rb_tree_tag,
      __gnu_pbds::tree_order_statistics_node_update>;

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
  int id;
  bool rev;
};

struct node final : splay_node_base<node, void, data_t> {
  using splay_node_base<node, void, data_t>::splay_node_base;
  void put() {
    value.rev ^= 1;
    swap(left, right);
  }
  void push() {
    if (value.rev) {
      if (left != nil) left->put();
      if (right != nil) right->put();
      value.rev = 0;
    }
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

  fast_input cin;

  int T;
  cin >> T;
  while(T--) {
    int n, m;
    cin >> n >> m;
    vector<int> perm(n+1), inv(n+1);
    for(int i=1; i<=n; i++) {
      cin >> perm[i];
      inv[perm[i]] = i;
    }

    vector<node*> h_node(n+1), v_node(n+1);
    splay_tree<node> h_tree(1), v_tree(1);
    for(int i=1; i<=n; i++) {
      h_node[i] = h_tree.push_back(data_t(perm[i], false));
      v_node[i] = v_tree.push_back(data_t(inv[i], false));
    }

    while(m--) {
      int t;
      cin >> t;
      if(t == 1) {
        int l, r;
        cin >> l >> r;
        h_tree.update_range(l, r);
      } else if(t == 2) {
        int l, r;
        cin >> l >> r;
        v_tree.update_range(l, r);
      } else if(t == 3) {
        int i, ai;
        cin >> i >> ai;
        n += 1; // new id
        h_node.push_back(h_tree.insert_before(i, data_t(n, false)));
        v_node.push_back(v_tree.insert_before(ai, data_t(n, false)));
      } else if(t == 4) {
        int i;
        cin >> i;
        cout << v_tree.rank(v_node[h_tree[i].id]) << nl;
      } else if(t == 5) {
        int ai;
        cin >> ai;
        cout << h_tree.rank(h_node[v_tree[ai].id]) << nl;
      } else {
        assert(false);
      }
    }
  }

  return 0;
}
