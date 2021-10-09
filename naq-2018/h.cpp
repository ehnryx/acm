#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef __float128 ll; // BEWARE
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
//const ll INFLL = 0x3f3f3f3f3f3f3f3f;
//const ll MOD = 1e9+7;
const ll EPS = 1e-7;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

////////////////////////////////////////////////////////////////////////////////
// Super Ultra Short Dynamic Hull   TESTED WF-2011-F USACO201502-C
////////////////////////////////////////////////////////////////////////////////
//*!
//*/
// WARNING: could overflow for values ~1e9, use __int128 instead
// WARNING: tested only with integer and rational types
const ll is_query = -1e42;
//const ll is_query = -(1LL<<62);
struct Line {
  ll m, b;
  mutable function<const Line*()> succ;
  bool operator<(const Line& rhs) const {
    if (rhs.b != is_query) return m < rhs.m;
    const Line* s = succ();
    if (!s) return 0;
    ll x = rhs.m;
    return b - s->b < (s->m - m) * x;
  }
};
// will maintain upper hull for maximum
struct HullDynamic : public multiset<Line> {
  bool bad(iterator y) {
    auto z = next(y);
    if (y == begin()) {
      if (z == end()) return 0;
      return y->m == z->m && y->b <= z->b;
    }
    auto x = prev(y);
    if (z == end()) return y->m == x->m && y->b <= x->b;
    // could overflow
    return (x->b - y->b)*(z->m - y->m) >= (y->b - z->b)*(y->m - x->m);
  }
  void insert_line(ll m, ll b) { m = -m; b = -b; // for lower hull
    auto y = insert({ m, b });
    y->succ = [=] { return next(y) == end() ? 0 : &*next(y); };
    if (bad(y)) { erase(y); return; }
    while (next(y) != end() && bad(next(y))) erase(next(y));
    while (y != begin() && bad(prev(y))) erase(prev(y));
  }
  ll eval(ll x) {
    auto l = *lower_bound((Line) { x, is_query });
    //return l.m * x + l.b; // for upper hull
  return -(l.m * x + l.b); // for lower hull
  }
};

//#define FILEIO
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);
#ifdef FILEIO
  freopen("test.in", "r", stdin);
  freopen("test.out", "w", stdout);
#endif

  ld in;
  ll n; int p, c;
  cin >> in >> p >> c;
  n = in;

  HullDynamic hull;
  hull.insert_line(1,0);
  ll ans = n;
  for (int i=0; i<p; i++) {
    ll t; int x, y;
    cin >> in >> x >> y;
    t = in;
    ll age = hull.eval(t);
    ll m = (ll)y/x;
    ll b = age+c - m*t;
    hull.insert_line(m, b);
    ans = max(ans, (n-b)/m);
  }

  cout << (ld)ans << nl;

  return 0;
}
