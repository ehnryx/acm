#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include "../../lca/number/mod_int.h"
#include "../../lca/data_structure/splay_tree.h"

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

using Int = mod_int<MOD>;

struct data_t {
  Int v, sum, m, b;
  bool rev;
  data_t(): v(0), sum(0), m(1), b(0), rev(0) {}
  data_t(int _v): v(_v), sum(_v), m(1), b(0), rev(0) {}
};

struct node final : splay_node_base<node, void, data_t> {
  using base = splay_node_base<node, void, data_t>;
  node(): base() {}
  node(int v): base(data_t(v)) {}
  void put() {
    swap(left, right);
    value.rev ^= 1;
  }
  void put(Int m, Int b) {
    value.v.assign(((ll)value.v.value() * m.value() + b.value()) % MOD);
    value.sum.assign(((ll)value.sum.value() * m.value() + (ll)b.value() * size) % MOD);
    value.m *= m;
    value.b.assign(((ll)value.b.value() * m.value() + b.value()) % MOD);
    //value.v = value.v * m + b;
    //value.sum = value.sum * m + b * size;
    //value.m = value.m * m;
    //value.b = value.b * m + b;
  }
  Int get() { return value.sum; }
  void push() {
    if(value.rev) {
      if (left != nil) left->put();
      if (right != nil) right->put();
      value.rev = 0;
    }
    if (value.m != 1 || value.b != 0) {
      if (left != nil) left->put(value.m, value.b);
      if (right != nil) right->put(value.m, value.b);
      value.m.assign(1);
      value.b.assign(0);
    }
  }
  void pull() {
    value.sum = value.v + left->value.sum + right->value.sum;
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

  static const int M = 1e6;
  splay_tree<node, M> st;

  int n, q;
  cin >> n >> q;

  for(int i=0; i<n; i++) {
    int a;
    cin >> a;
    st.push_back(a);
  }

  while(q--) {
    int t;
    cin >> t;
    if(t == 0) {
      int i, x;
      cin >> i >> x;
      st.insert_before(i, x);
    } else if(t == 1) {
      int i;
      cin >> i;
      st.erase_at(i);
    } else if(t == 2) {
      int l, r;
      cin >> l >> r;
      st.update_range(l, r - 1);
    } else if(t == 3) {
      int l, r, m, b;
      cin >> l >> r >> m >> b;
      st.update_range(l, r - 1, m, b);
    } else if(t == 4) {
      int l, r;
      cin >> l >> r;
      cout << st.query_range(l, r - 1) << nl;
    }
  }

  return 0;
}
