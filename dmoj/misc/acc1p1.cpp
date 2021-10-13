#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include "../../../lca/data_structure/splay_tree.h"

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

struct node_data {
  int ans, pref, suff;
  bool val, rev;
  node_data(): ans(-INF), pref(0), suff(0), val(0), rev(0) {}
  node_data(int v): ans(v), pref(v), suff(v), val(v), rev(0) {}
};

struct node final : splay_node_range<node, void, node_data, int> {
  using base_node = splay_node_range<node, void, node_data, int>;
  node(): base_node() {}
  node(int v): base_node(node_data(v)) {}
  void put(void*) {
    value.rev ^= 1;
    swap(left, right);
    swap(value.pref, value.suff);
  }
  int get(void*) { return value.ans; }
  void push() {
    if(value.rev) {
      if(left != nil) left->put(nullptr);
      if(right != nil) right->put(nullptr);
      value.rev = 0;
    }
  }
  void pull() {
    value.ans = max((int)value.val, max(left->value.ans, right->value.ans));
    value.pref = left->value.pref;
    value.suff = right->value.suff;
    if (value.val) {
      value.ans = max(value.ans, left->value.suff + right->value.pref + value.val);
      if (left->size == left->value.pref) {
        value.pref = left->value.pref + value.val + right->value.pref;
      }
      if (right->size == right->value.suff) {
        value.suff = left->value.suff + value.val + right->value.suff;
      }
    }
  }
};

using splaytree = splay_tree<node, 100'000>;

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

  splaytree st;

  int n, m;
  cin >> n >> m;
  for(int i=0; i<n; i++) {
    char c;
    cin >> c;
    st.push_back(c - '0');
  }

  while(m--) {
    int t, s, l;
    cin >> t >> s >> l;
    if(t == 1) {
      st.update_range(s, s+l-1, nullptr);
    } else {
      cout << st.query_range(s, s+l-1, nullptr) << nl;
    }
    //for(const auto& it : st) {
      //cerr << it.val << " ";
    //} cerr << nl;
  }

  return 0;
}
