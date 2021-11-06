#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

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

struct data_t {
  ll val, sum;
  data_t(): val(0), sum(0) {}
  data_t(int v): val(v), sum(v) {}
};

struct node final : splay_node_range<node, void, data_t, ll> {
  using base = splay_node_range<node, void, data_t, ll>;
  node(): base() {}
  node(int v): base(data_t(v)) {}
  void put(void* v) {
    value.val += *(ll*)v;
    pull();
  }
  ll get(void*) { return value.sum; }
  void push() {}
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

  static const int M = 5e5;
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
      int i; ll x;
      cin >> i >> x;
      st.at(i)->put(&x);
    } else {
      int l, r;
      cin >> l >> r;
      cout << st.query_range(l, r-1, nullptr) << nl;
    }
  }

  return 0;
}
