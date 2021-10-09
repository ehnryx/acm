#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include "../../lca/data_structure/segment_tree.h"

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

struct summer {
  ll sum;
  summer() = default;
  void put(ll v) { sum = v; }
  ll get() const { return sum; }
  void pull(const summer& a, const summer& b) {
    sum = a.sum + b.sum;
  }
  bool contains(ll& x) {
    if(x < sum) return true;
    x -= sum;
    return false;
  }
  static ll default_value() { return 0; }
  static ll merge(ll a, ll b) { return a + b; }
};

struct node {
  ll val, lazy;
  int alive;
  node() = default;
  void put(ll v, int a) { val = v; alive = a; }
  void put(ll v) { val += v; lazy += v; }
  int get() const { return alive; }
  void pull(const node& a, const node& b) {
    val = min(a.val, b.val);
    alive = a.alive + b.alive;
  }
  void push(node& a, node& b) {
    if(lazy) {
      a.put(lazy);
      b.put(lazy);
      lazy = 0;
    }
  }
  static int default_value() { return 0; }
  static int merge(int a, int b) { return a + b; }
  bool contains(ll x) {
    //cerr << x << " vs " << val << nl;
    return val < x;
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

  int n;
  cin >> n;
  segment_tree<summer, ll, false> sum(n+1);
  segment_tree<node, int> st(n+1);

  vector<int> a(n+1);
  vector<ll> b(n+1);
  for(int i=1; i<=n; i++) {
    cin >> a[i] >> b[i];
    sum.update_point(i, a[i]);
    //cerr << "put " << i << " " << a[i] << " " << b[i] << " w/ " << sum.query_range(1, i) + b[i] << nl;
    st.update_point(i, sum.query_range(1, i) + b[i], 1);
  }

  int q;
  cin >> q;
  while(q--) {
    int t;
    cin >> t;
    if(t == 2) {
      int atmp;
      ll btmp;
      int i;
      cin >> atmp >> btmp >> i;
      //cerr << "update " << i << " " << atmp << " " << btmp << endl;
      st.update_range(i, n, atmp - a[i]);
      a[i] = atmp;
      b[i] = btmp;
      sum.update_point(i, a[i]);
      st.update_point(i, sum.query_range(1, i) + b[i], 1);
      continue;
    }

    ll x;
    cin >> x;
    //cerr << "QUERY " << x << endl;
    int rb = sum.search_left(1, n, x); // leftmost sum a_i > x
    int starve = st.query(rb, n);
    //cerr << "rb = " << rb << endl;
    int dead = 0;
    for(int die; (die = st.search_right(1, rb - 1, x)) != st.lim; ) {
      //cerr << "DIE: " << die << endl;
      st.update_range(die, n, -a[die]);
      sum.update_point(die, 0);
      st.update_point(die, INFLL, 0);
      dead += 1;
      rb = die;
      a[die] = 0;
    }
    cout << dead << " " << starve << nl;
  }

  return 0;
}
