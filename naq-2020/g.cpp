//#pragma GCC optimize("O3")
//#pragma GCC optimize("fast-math")
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

struct Line {
    mutable ld m, b, p;
    bool operator<(const Line& o) const { return m < o.m; }
    bool operator<(ld x) const { return p < x; }
};

struct LineContainer : multiset<Line, less<>> {
    const ld inf = (ld)1 / (ld)0;
    //ld div(ld a, ld b) { // floored division
        //return a / b - ((a ^ b) < 0 && a % b); }
  ld div(ld a, ld b) { return a/b; }
    bool isect(iterator x, iterator y) {
        if (y == end()) { x->p = inf; return false; }
        if (x->m == y->m) x->p = x->b > y->b ? inf : -inf;
        else x->p = div(y->b - x->b, x->m - y->m);
        return x->p >= y->p;
    }
    void add(ld m, ld b) {
        auto z = insert({m, b, 0}), y = z++, x = y;
        while (isect(y, z)) z = erase(z);
        if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
        while ((y = x) != begin() && (--x)->p >= y->p)
            isect(x, erase(y));
    }
    ld query(ld x) {
        assert(!empty());
        auto l = *lower_bound(x);
        return l.m * x + l.b;
    }
};


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

  int n;
  cin >> n;
  ld k;
  cin >> k;

  LineContainer lc;
  vector<ld> h(n+2);
  for(int i=1; i<=n; i++) {
    cin >> h[i];
  }
  for(int i=0; i<=n+1; i++) {
    ld m = - 2*k * i;
    ld b = h[i] + k*i*i;
    lc.add(m, b);
  }

  ld l = 0;
  ld r = n+1;
  for(int bs=0; bs<200; bs++) {
    ld lm = (5*l + 4*r) / 9;
    ld rm = (4*l + 5*r) / 9;
    ld lv = lc.query(lm) + k*lm*lm;
    ld rv = lc.query(rm) + k*rm*rm;
    if(lv < rv) {
      r = rm;
    } else {
      l = lm;
    }
  }
  assert(abs(l-r) < EPS);

  ld a = floor(r);
  ld b = ceil(r);
  ld v = lc.query(r) + k*r*r;
  ld top = max(v - k*(r-a)*(r-a), v - k*(r-b)*(r-b));
  cout << top << nl;

  return 0;
}
