#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include "../../../lca/data_structure/segment_tree.h"
#include "../../../lca/tree/range_query_tree.h"

//#define FILENAME sadcactus

/*
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
template <typename T>
using ordered_set = __gnu_pbds::tree<T,
      __gnu_pbds::null_type,
      less<T>,
      __gnu_pbds::rb_tree_tag,
      __gnu_pbds::tree_order_statistics_node_update>;
      */

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int INF = 0x3f3f3f3f;
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;
constexpr int MOD = 1e9 + 7;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

int K;

struct node {
  int sum, prod, minv, maxv, g, _and, _or, _xor, big, small, minbig, maxsmall;
  int high;
  node():
    sum(0),
    prod(1),
    minv(INF),
    maxv(-INF),
    g(0),
    _and(~0),
    _or(0),
    _xor(0),
    big(0),
    small(0),
    minbig(INF),
    maxsmall(-INF),
    high(0) {} // ??????

  void put(int v, int id) {
    sum = prod = minv = maxv = g = _and = _or = _xor = v;
    big = v > K;
    small = v < K;
    minbig = v > K ? v : INF;
    maxsmall = v < K ? v : -INF;
    high = id; // fingers going numb
  }
  const node& get() const { return *this; }
  node pull(const node& a, const node& b) {
    sum = a.sum + b.sum;
    prod = (ll)a.prod * b.prod % MOD;
    minv = min(a.minv, b.minv);
    maxv = max(a.maxv, b.maxv);
    g = gcd(a.g, b.g);
    _and = a._and & b._and;
    _or = a._or | b._or;
    _xor = a._xor ^ b._xor;
    big = a.big + b.big;
    small = a.small + b.small;
    minbig = min(a.minbig, b.minbig);
    maxsmall = max(a.maxsmall, b.maxsmall);
    high = max(a.high, b.high); // what the fuck
    return *this;
  }
  void push(node&, node&) {}
  static node merge(const node& a, const node& b) { return node().pull(a, b); }
  static node default_value() { assert(false); }
};

using segtree = segment_tree<node, node>;

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

  int n, q, k;
  cin >> n >> q >> k;
  K = k; // what the heck

  vector<int> val(n+1);
  for(int i=1; i<=n; i++) {
    cin >> val[i];
  }

  vector<vector<int>> adj(n+1);
  for(int i=1; i<n; i++) {
    int a, b;
    cin >> a >> b;
    adj[a].emplace_back(b);
    adj[b].emplace_back(a);
  }

  range_query_tree<segtree, node> tree(adj, 1);
  for(int i=1; i<=n; i++) {
    tree.update_point(i, val[i], i);
  }

  node init = node();

  int root = 1;
  while(q--) {
    int t;
    cin >> t;
    int a, b;
    if(t == 1) cin >> a;
    else cin >> a >> b;
    if(t == 1) {
      root = a;
    } else if(t == 2) {
      /*
      int c = tree.lca(a, b);
      int ra = tree.lca(a, root);
      int rb = tree.lca(b, root);
      if(ra == rb) cout << c << nl;
      else if(ra == c) cout << rb << nl;
      else if(rb == c) cout << ra << nl;
      else assert(false);
      */
      cout << root << nl; // WHAT THE FUCK ???
      //int c = tree.lca(a, b); /// ???? what is a "highest common ancestor"
      //cout << tree.query_path(c, root, true, init, node::merge).high << nl;
    } else if(t == 3) {
      cout << tree.query_path(a, b, true, init, node::merge).sum << nl;
    } else if(t == 4) {
      cout << tree.query_path(a, b, true, init, node::merge).prod << nl;
    } else if(t == 5) {
      cout << tree.query_path(a, b, true, init, node::merge).minv << nl;
    } else if(t == 6) {
      cout << tree.query_path(a, b, true, init, node::merge).maxv << nl;
    } else if(t == 7) {
      cout << tree.query_path(a, b, true, init, node::merge).g << nl;
    } else if(t == 8) {
      cout << tree.query_path(a, b, true, init, node::merge)._and << nl;
    } else if(t == 9) {
      cout << tree.query_path(a, b, true, init, node::merge)._or << nl;
    } else if(t == 10) {
      cout << tree.query_path(a, b, true, init, node::merge)._xor << nl;
    } else if(t == 11) {
      cout << tree.query_path(a, b, true, init, node::merge).big << nl;
    } else if(t == 12) {
      cout << tree.query_path(a, b, true, init, node::merge).small << nl;
    } else if(t == 13) {
      int res = tree.query_path(a, b, true, init, node::merge).minbig;
      if(res == INF) cout << K << nl;
      else cout << res << nl;
    } else if(t == 14) {
      int res = tree.query_path(a, b, true, init, node::merge).maxsmall;
      if(res == -INF) cout << K << nl;
      else cout << res << nl;
    } else assert(false);
  }

  return 0;
}
