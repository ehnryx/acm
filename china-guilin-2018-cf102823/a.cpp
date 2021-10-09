#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

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
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

struct Line {
  mutable ld m, b, p;
  bool operator<(const Line& o) const { return m < o.m; }
  bool operator<(ld x) const { return p < x; }
};

struct LineContainer : multiset<Line, less<>> {
  const ld inf = 1/(ld)0;
  ld div(ld a, ld b) { return a/b; }
  bool isect(iterator x, iterator y) {
    if (y == end()) { x->p = inf; return false; }
    if (x->m == y->m) x->p = x->b > y->b ? inf : -inf;
    else x->p = div(y->b - x->b, x->m - y->m);
    return x->p >= y->p;
  }
  void add(ld m, ld b) { m = -m; b = -b;
    auto z = insert({m, b, 0}), y = z++, x = y;
    while (isect(y, z)) z = erase(z);
    if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
    while ((y = x) != begin() && (--x)->p >= y->p)
      isect(x, erase(y));
  }
  pair<ld,int> query(ld x) {
    assert(!empty());
    auto l = *lower_bound(x);
    return pair(-l.m * x + -l.b, (int)round(-l.m));
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

  int T;
  cin >> T;
  for(int testnum=1; testnum<=T; testnum++) {
    cout << "Case " << testnum << ": ";

    int n, m;
    cin >> n >> m;
    vector<ll> a(n+1), b(m+1);
    ll sum = 0;
    for(int i=1; i<=n; i++) {
      cin >> a[i];
      sum += a[i] * i;
    }
    for(int i=1; i<=m; i++) {
      cin >> b[i];
      sum += b[i] * i;
    }
    vector<ll> pb, pa;
    partial_sum(a.begin(), a.end(), back_inserter(pa));
    partial_sum(b.begin(), b.end(), back_inserter(pb));

    LineContainer hull;
    for(int i=0; i<=n; i++) {
      hull.add(i, pa[n] - pa[i]);
    }

    ll ans = sum;
    vector<tuple<int,int,ll>> memo; // [pos, size of group]
    for(int i=1; i<=m; i++) {
      auto [val, j] = hull.query(b[i]);
      int sz = 1;
      while(!memo.empty() && j < get<0>(memo.back())) {
        sz += get<1>(memo.back());
        ans -= get<2>(memo.back());
        memo.pop_back();
        tie(val, j) = hull.query((pb[i] - pb[i-sz]) / (ld)sz);
      }
      ll cur = llround(val * sz);
      memo.emplace_back(j, sz, cur);
      ans += cur;
    }
    cout << ans << nl;
  }

  return 0;
}
