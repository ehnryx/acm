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

struct internal_node {
  char c;
  bool rev;
  internal_node(char _c, bool _r): c(_c), rev(_r) {}
};

using base_node = splay_node_range<void, internal_node>;
struct node : base_node {
  node(internal_node v): base_node(v) {}
  void put(const any&) override {
    value.rev ^= 1;
    swap(left, right);
  }
  void get(const any&) override {}
  void push() override {
    if (value.rev) {
      if(left) left->put(value.rev);
      if(right) right->put(value.rev);
      value.rev = 0;
    }
  }
  void pull() override {}
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

  int n, l, r;
  cin >> n >> l >> r;
  l -= 1;
  r -= 1;

  string s;
  cin >> s;
  splay_tree<base_node, true> st;
  for(char c : s) {
    st.push_back<node>(internal_node(c, false));
  }

  string ans;

  int q;
  cin >> q;
  while(q--) {
    char t;
    cin >> t;
    if(t == 'Q') {
      char head;
      cin >> head;
      ans.push_back(st.at(head == 'L' ? l : r)->value.c);
    } else if(t == 'S') {
      char head, dir;
      cin >> head >> dir;
      (head == 'L' ? l : r) += (dir == 'L' ? -1 : 1);
    } else {
      st.update_range(l, r, 1);
    }
  }

  cout << ans << nl;

  return 0;
}
