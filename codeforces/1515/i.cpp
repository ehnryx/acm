#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include "../../../lca/data_structure/fenwick_tree.h"

//#define FILENAME sadcactus

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;
typedef long double ld;
typedef complex<ld> pt;

constexpr char nl = '\n';
constexpr ll INF = 0x3f3f3f3f;
constexpr ll INFLL = 0x3f3f3f3f3f3f3f3f;
constexpr ll MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

const int L = 18;
const int N = 1 << 18;

struct segtree {
  int n, lim;
  vector<ll> value, lazy;
  segtree(int len): n(1 << (32 - __builtin_clz(len))), lim(len), value(2*n), lazy(2*n) {}
  void update(int l, int r, ll v) { update(l, r, v, 1, 0, n-1); }
  void update(int l, int r, ll v, int i, int s, int e) {
    if(r<s || e<l) return;
    if(l<=s && e<=r) return put(i, v);
    push(i);
    int m = (s+e)/2;
    update(l, r, v, 2*i, s, m);
    update(l, r, v, 2*i+1, m+1, e);
    pull(i);
  }
  void pull(int i) { value[i] = min(value[2*i], value[2*i+1]); }
  void push(int i) {
    if(lazy[i]) {
      put(2*i, lazy[i]);
      put(2*i+1, lazy[i]);
      lazy[i] = 0;
    }
  }
  void put(int i, ll v) {
    value[i] += v;
    lazy[i] += v;
  }
  int search_left(int l, int r, ll v) { return search_left(l, r, v, 1, 0, n-1); }
  int search_left(int l, int r, ll v, int i, int s, int e) {
    if(r<s || e<l) return lim;
    if(l<=s && e<=r && value[i] > v) return lim;
    if(s == e) return s;
    push(i);
    int m = (s+e)/2;
    int res = search_left(l, r, v, 2*i, s, m);
    if(res == lim) res = search_left(l, r, v, 2*i+1, m+1, e);
    return res;
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

  vector<ll> a(n);
  vector<int> w(n), v(n);
  vector<tuple<int,int,int>> order;
  for(int i=0; i<n; i++) {
    cin >> a[i] >> w[i] >> v[i];
    order.emplace_back(-v[i], w[i], i);
  }
  sort(begin(order), end(order));
  vector<int> remap(n);
  for(int i=0; i<n; i++) {
    remap[get<2>(order[i])] = i;
  }

  // build trees
  //vector values(L, segment_tree<Sum, ll, false>(n));
  //vector weights(L, segment_tree<Sum, ll, false>(n));
  vector values(L, fenwick_tree<ll>(n));
  vector weights(L, fenwick_tree<ll>(n));
  vector equal(L, segtree(n));
  for(int i=0; i<n; i++) {
    // (v[i], w[i]) at remap[i]
    int id = remap[i];
    ll weight = a[i] * w[i];
    ll value = a[i] * v[i];
    for(int j=0; j<L; j++) {
      if(w[i] < 1 << j) {
        //values[j].update_point(id, value);
        //weights[j].update_point(id, weight);
        values[j].update(id, value);
        weights[j].update(id, weight);
        equal[j].update(id, n-1, weight);
      }
      if(1 << j <= w[i] && w[i] < 1 << (j+1)) {
        equal[j].update(id, id, w[i] + (a[i] == 0 ? INFLL : 0));
      } else {
        equal[j].update(id, id, INFLL);
      }
    }
  }

  function<void(int,int)> update = [&](int i, ll cnt) {
    int id = remap[i];
    ll weight = cnt * w[i];
    ll value = cnt * v[i];
    for(int j=0; j<L; j++) {
      if(w[i] < 1 << j) {
        //values[j].update_point(id, value);
        //weights[j].update_point(id, weight);
        values[j].update(id, value);
        weights[j].update(id, weight);
        equal[j].update(id, n-1, weight);
      }
      if(1 << j <= w[i] && w[i] < 1 << (j+1)) {
        if(a[i] + cnt == 0) {
          equal[j].update(id, id, INFLL);
        } else if(a[i] == 0) {
          equal[j].update(id, id, -INFLL);
        }
      }
    }
    a[i] += cnt;
  };

  // solver
  function<ll(int,ll,int)> solve = [&](int lvl, ll cap, int s) -> ll {
    if(lvl < 0 || s >= n) return 0;
    if(cap < 1 << lvl) return solve(lvl - 1, cap, s);
    ll prefix = weights[lvl].query(0, s - 1);
    //int small = weights[lvl].search_left(s, n - 1, cap);
    int small = weights[lvl].lower_bound(cap + prefix + 1);
    int big = equal[lvl].search_left(s, n - 1, cap + prefix);
    if(small == n && big == n) { // take everything
      return values[lvl].query(s, n - 1);
    } else if(big < small) { // take the big one
      int j = get<2>(order[big]);
      cap -= weights[lvl].query(s, big) + w[j];
      return values[lvl].query(s, big) + v[j] + solve(lvl - 1, cap, big + 1);
    } else { // take the small ones
      int j = get<2>(order[small]);
      cap -= weights[lvl].query(s, small - 1);
      ll take = cap / w[j];
      return values[lvl].query(s, small - 1) + take * v[j]
        + solve(lvl - 1, cap - take * w[j], small + 1);
    }
  };

  for(int i=0; i<m; i++) {
    int t;
    cin >> t; if(t == 1) {
      int k, d;
      cin >> k >> d;
      update(d - 1, k);
    } else if(t == 2) {
      int k, d;
      cin >> k >> d;
      update(d - 1, -k);
    } else {
      ll cap;
      cin >> cap;
      cout << solve(L - 1, cap, 0) << nl;
    }
  }

  return 0;
}
