//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
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

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 998244353;
const ld EPS = 1e-9;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

typedef long double LT;

struct Line {
  mutable LT m, b, p;
  bool operator<(const Line& o) const { return m < o.m; }
  bool operator<(LT x) const { return p < x; }
};

struct LineContainer : multiset<Line, less<>> {
  // (for doubles, use inf = 1/.0, div(a,b) = a/b)
  const LT inf = 1/.0;
  LT div(LT a, LT b) { return a/b; }
  /*
  const LT inf = LLONG_MAX;
  LT div(LT a, LT b) { // floored division
    return a / b - ((a ^ b) < 0 && a % b); } */
  bool isect(iterator x, iterator y) {
    if (y == end()) { x->p = inf; return false; }
    if (x->m == y->m) x->p = x->b > y->b ? inf : -inf;
    else x->p = div(y->b - x->b, x->m - y->m);
    return x->p >= y->p;
  }
  void add(LT m, LT b) {
    auto z = insert({m, b, 0}), y = z++, x = y;
    while (isect(y, z)) z = erase(z);
    if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
    while ((y = x) != begin() && (--x)->p >= y->p)
      isect(x, erase(y));
  }
  LT query(LT x) {
    if(empty()) return -INFLL;
    auto l = *lower_bound(x);
    return l.m * x + l.b;
  }
};

const int N = 1 << 17;
LineContainer st[2*N];

void insert(int x, int m, int b, int M) {
  st[x += M].add(m, b);
  for(x/=2; x; x/=2) {
    st[x].add(m, b);
  }
}

int query(int l, LT x, LT b, int i, int s, int e) {
  if(e < l) return 0;
  if(st[i].query(x) < b + EPS) return 0;
  if(s == e) return s;
  int m = (s+e) / 2;
  int left = query(l, x, b, 2*i, s, m);
  if(left) return left;
  return query(l, x, b, 2*i+1, m+1, e);
}

// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);
#if defined(ONLINE_JUDGE) && defined(FILENAME)
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif

  int T;
  cin >> T;
  while(T--) {
    int n;
    cin >> n;
    vector<int> x(n), y(n);
    for(int i=0; i<n; i++) {
      cin >> x[i] >> y[i];
    }
    int m = 1 << (32 - __builtin_clz(n-1));

    for(int i=1; i<2*m; i++) {
      st[i].clear();
    }
    for(int i=0; i<n; i++) {
      insert(i, -x[i], y[i], m);
    }

    vector<int> ans;
    for(int i=1; i<n; i++) {
      ld slope = (ld)(y[i]-y[i-1]) / (x[i]-x[i-1]);
      ld inter = y[i] - slope*x[i];
      int cur = query(i, slope, inter, 1, 0, m-1);
      ans.push_back(cur);
    }

    for(int it : ans) {
      cout << it << " ";
    }
    cout << nl;
  }

  return 0;
}
