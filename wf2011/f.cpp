#include <bits/stdc++.h>
using namespace std;

#define nl '\n'

typedef long long ll;
typedef long double ld;
typedef complex<ld> pt;
typedef pair<int,int> pii;


const ll is_query = -(1LL<<62);
struct Line {
  ll m, b;
  mutable function<const Line*()> succ;
  bool operator<(const Line&rhs) const {
    if (rhs.b != is_query) return m<rhs.m;
    const Line* s=succ();
    if (!s) return 0;
    ll x = rhs.m;
    return b-s->b < (ld)(s->m - m) * x;
  }
};

struct HullDynamic : public multiset<Line> {
  bool bad(iterator y) {
    auto z = next(y);
    if (y==begin()) {
      if (z==end()) return 0;
      return y->m == z->m && y->b <=z->b;
    }
    auto x = prev(y);
    if (z==end()) return y->m == x->m && y->b <=x->b;
    return (ld)(x->b - y->b)*(z->m - y->m) >= (ld)(y->b - z->b)*(y->m -x->m); // OVERFLOW!
  }
  void insert_line(ll m, ll b) {
    auto y = insert({m,b});
    y->succ = [=] { return next(y) == end() ? 0:&*next(y); };
    if (bad(y)) { erase(y); return; }
    while(next(y) != end() && bad(next(y))) erase(next(y));
    while(y!=begin() &&  bad(prev(y))) erase(prev(y));
  }

  ll eval(ll x) {
    auto l = *lower_bound((Line) {x, is_query});
    return l.m*x + l.b;
  }
};

int n, c, d;

struct machine {
  ll d, p, r, g;
  bool operator < (const machine& o) const {
    return d < o.d;
  }
};

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int it = 1;
  for(;cin >> n >> c >> d && n;) {
    cout << "Case " << it++ << ": ";
    vector<machine> mach;
    for(int i=0;i<n;i++) {
      int dd, pp, rr, gg;
      cin >> dd >> pp >> rr >> gg;
      mach.push_back({dd,pp,rr,gg});
    }
    HullDynamic hd;
    hd.insert_line(0, c);
    sort(mach.begin(), mach.end());
    for(auto &m: mach) {
      ll money = hd.eval(m.d);
      //cerr << "@time " << m.d << " have money " << money <<endl;
      if (money >= m.p) {
        hd.insert_line(m.g, money - m.p+m.r-m.g*(m.d+1));
      }
    }
    ll ans = hd.eval(d+1);
    cout << ans <<endl;
  }


  return 0;
}
