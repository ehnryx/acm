#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long lli;
typedef long double ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;
#define nl '\n'

///* advent of code
typedef istringstream iss;
#define pb push_back
#define ins insert
#define multiset mset
#define getl(A) getline(cin, A)
//*/

////////////////////////////////////////////////////////////////////////////////
// Super Ultra Short Dynamic Hull   TESTED WF-2011-F USACO201502-C
////////////////////////////////////////////////////////////////////////////////
// WARNING: could overflow for values ~1e9, use __int128 instead
// WARNING: tested only with integer and rational types
// typedef __int128 ll;

const ll is_query = -(1LL<<62);
struct Line {
  ll m, b;
  ll cost;
  int id;
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

  void insert_line(ll m, ll b, ll cost, int id) {
    auto y = insert({ m, b, cost, id });
    y->succ = [=] { return next(y) == end() ? 0 : &*next(y); };
    if (bad(y)) { erase(y); return; }
    while (next(y) != end() && bad(next(y))) erase(next(y));
    while (y != begin() && bad(prev(y))) erase(prev(y));
  }

  Line eval(ll x) {
    return *lower_bound((Line) { x, is_query });
  }
};
////////////////////////////////////////////////////////////////////////////////

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);

  int n, m, f;
  cin >> n >> m >> f;

  vector<int> v(n+1);
  for (int i = 0; i < n; i++) {
    cin >> v[i];
  }
  v[n] = 0;

  HullDynamic chull;

  lli ans = m;
  int prev[n+1];
  lli value[n+1];
  memset(prev, -1, sizeof(prev));
  memset(value, 0, sizeof(value));

  for (int i = 0; i < n; i++) {
    auto res = chull.eval(v[i]);
  }

  return 0;
}
