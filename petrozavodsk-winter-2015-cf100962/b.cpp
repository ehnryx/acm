#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
const ld EPS2 = 1e-4;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

bool eq(const ld& a, const ld& b) {
  return abs(a-b) < EPS;
}

//*/
// WARNING: could overflow for values ~1e9, use __int128 instead
// WARNING: tested only with integer and rational types
// typedef __int128 ll;
const ld is_query = -(1LL<<62);
struct Line {
  ld m, b;
  mutable function<const Line*()> succ;
  bool operator<(const Line& rhs) const {
    if (rhs.b != is_query) return m < rhs.m;
    const Line* s = succ();
    if (!s) return 0;
    ld x = rhs.m;
    return b - s->b < (s->m - m) * x;
  }
};
// will maintain upper hull for maximum
struct UpperHullDynamic : public multiset<Line> {
  bool bad(iterator y) {
    auto z = next(y);
    if (y == begin()) {
      if (z == end()) return 0;
      return eq(y->m, z->m) && y->b <= z->b;
    }
    auto x = prev(y);
    if (z == end()) return eq(y->m, x->m) && y->b <= x->b;
    // could overflow
    return (x->b - y->b)*(z->m - y->m) >= (y->b - z->b)*(y->m - x->m);
  }
  void insert_line(ld m, ld b) { // m = -m; b = -b; // for lower hull
    auto y = insert({ m, b });
    y->succ = [=] { return next(y) == end() ? 0 : &*next(y); };
    if (bad(y)) { erase(y); return; }
    while (next(y) != end() && bad(next(y))) erase(next(y));
    while (y != begin() && bad(prev(y))) erase(prev(y));
  }
  ld eval(ld x) {
    auto l = *lower_bound((Line) { x, is_query });
    return l.m * x + l.b; // return -(l.m * x + l.b); // for lower hull
  }
};
// will maintain upper hull for minimum
struct LowerHullDynamic : public multiset<Line> {
  bool bad(iterator y) {
    auto z = next(y);
    if (y == begin()) {
      if (z == end()) return 0;
      return eq(y->m, z->m) && y->b <= z->b;
    }
    auto x = prev(y);
    if (z == end()) return eq(y->m, x->m) && y->b <= x->b;
    // could overflow
    return (x->b - y->b)*(z->m - y->m) >= (y->b - z->b)*(y->m - x->m);
  }
  void insert_line(ld m, ld b) { m = -m; b = -b; // for lower hull
    auto y = insert({ m, b });
    y->succ = [=] { return next(y) == end() ? 0 : &*next(y); };
    if (bad(y)) { erase(y); return; }
    while (next(y) != end() && bad(next(y))) erase(next(y));
    while (y != begin() && bad(prev(y))) erase(prev(y));
  }
  ld eval(ld x) {
    auto l = *lower_bound((Line) { x, is_query });
  return -(l.m * x + l.b); // for lower hull
  }
};

mt19937 luck(chrono::high_resolution_clock::now().time_since_epoch().count());

ld sqr(const ld& x) {
  return x*x;
}

struct Circle {
  int x, y, r;
};
pair<ld,ld> power(const Circle& a, const Circle& b) {
  ld L = sqrt(sqr(a.x-b.x)+sqr(a.y-b.y));
  ld x = (sqr(L)+sqr(a.r)-sqr(b.r)) / (2*L);
  return pair<ld,ld>(x/L, 1-x/L);
}

ld slope(const Circle& a, const Circle& b) {
  return (ld) (-1) * (a.x-b.x) / (a.y-b.y);
}

ld cp(const pt& a, const pt& b) { return imag(conj(a)*b); }
bool eq(const pt& a, const pt& b) { return abs(a-b) < EPS2; }
inline ld sgn(const ld& x) { return abs(x) < EPS ? 0 : x < EPS ? -1 : 1; }
inline bool cmp_lex(const pt& a, const pt& b) {
  return a.real()<b.real()-EPS||(a.real()<b.real()+EPS&&a.imag()<b.imag()-EPS);}
inline bool cmp_lex_i(const pt& a, const pt& b) {
  return a.imag()<b.imag()-EPS||(a.imag()<b.imag()+EPS&&a.real()<b.real()-EPS);}
// handles ALL cases, uncomment/edit the 3 marked lines to exclude endpoints
bool seg_x_seg(pt a1, pt a2, pt b1, pt b2) {
  //if (eq(a1,a2) || eq(b1,b2)) return false; // uncomment to exclude endpoints
  ld za = abs(a2-a1), zb = abs(b2-b1); za=za>EPS?1/za:0; zb=zb>EPS?1/zb:0;
  int s1 = sgn(cp(a2-a1, b1-a1)*za), s2 = sgn(cp(a2-a1, b2-a1)*za);
  int s3 = sgn(cp(b2-b1, a1-b1)*zb), s4 = sgn(cp(b2-b1, a2-b1)*zb);
  if(!s1 && !s2 && !s3) { // collinear
    if (cmp_lex(a2, a1)) swap(a1, a2); if (cmp_lex(b2, b1)) swap(b1, b2);
    //return cmp_lex(a1, b2) && cmp_lex(b1, a2);//uncomment to exclude endpoints
    return !cmp_lex(b2, a1) && !cmp_lex(a2, b1);
  } return s1*s2 <= 0 && s3*s4 <= 0; } //change to < to exclude endpoints
pt line_inter(const pt& a, const pt& b, const pt& c, const pt& d) {
  return a + cp(c-a, d-c) / cp(b-a, d-c) * (b-a);
}
pt line_inter(const Line& a, const Line& b) {
  return line_inter(pt(0,a.b), pt(10,a.b+10*a.m), pt(0,b.b), pt(10,b.b+10*b.m));
}


mt19937 more_luck(chrono::high_resolution_clock::now().time_since_epoch().count());

int w, h, n;
void solve(int id, const vector<Circle>& circles) {
  //cerr << nl << " SOLVE " << id << nl;
  ld left = 0;
  ld right = w;
  LowerHullDynamic uhull; uhull.insert_line(0, h);
  UpperHullDynamic lhull; lhull.insert_line(0, 0);

  for (int i=0; i<n; i++) {
    if (i == id) continue;

    ld p, q;
    tie(q,p) = power(circles[id], circles[i]);
    //cerr << "p: " << p << " q: " << q << nl;

    if (circles[id].y == circles[i].y) {
      ld x = p*circles[id].x + q*circles[i].x;
      if (x < circles[id].x) {
        //cerr << "upd left " << x << nl;
        left = max(left, x);
      } else {
        //cerr << "upd right " << x << nl;
        right = min(right, x);
      }
    }
    else {
      ld x = p*circles[id].x + q*circles[i].x;
      ld y = p*circles[id].y + q*circles[i].y;
      ld m = slope(circles[id], circles[i]);
      ld b = y-m*x;
      if (m*circles[id].x + b > circles[id].y) {
        //cerr << "insert upper " << m << ',' << b << nl;
        uhull.insert_line(m, b);
      } else {
        //cerr << "insert lower " << m << ',' << b << nl;
        lhull.insert_line(m, b);
      }
    }
  }

  //cerr << "U LINES: " << nl; for (const Line& it : uhull) {
    //cerr << "y = " << it.m << "x + " << it.b << nl; }
  //cerr << "L LINES: " << nl; for (const Line& it : lhull) {
    //cerr << "y = " << it.m << "x + " << it.b << nl; }

  vector<pt> upper, lower, points;
  pt inter;

  for (int round = 0; round < 2; round++) {
    upper.clear();
    lower.clear();

    upper.push_back(pt(left, uhull.eval(left)));
    for (auto it = next(uhull.begin()); it != uhull.end(); it++) {
      const Line& first = *prev(it);
      const Line& second = *it;
      inter = line_inter(first, second);
      if (left < inter.real() && inter.real() < right) {
        if (!eq(inter, upper.back())) {
          upper.push_back(pt(inter.real(), -inter.imag()));
        }
      }
    }
    inter = pt(right, uhull.eval(right));
    if (!eq(inter, upper.back())) {
      upper.push_back(inter);
    }

    lower.push_back(pt(left, lhull.eval(left)));
    for (auto it = next(lhull.begin()); it != lhull.end(); it++) {
      const Line& first = *prev(it);
      const Line& second = *it;
      pt inter = line_inter(first, second);
      if (left < inter.real() && inter.real() < right) {
        if (!eq(inter, lower.back())) {
          lower.push_back(inter);
        }
      }
    }
    inter = pt(right, lhull.eval(right));
    if (!eq(inter, lower.back())) {
      lower.push_back(inter);
    }

    //cerr << "Lower Envelope" << nl; for (const pt& it : lower)
      //cerr << it << " "; //cerr << nl;
    //cerr << "Upper Envelope" << nl; for (const pt& it : upper)
      //cerr << it << " "; //cerr << nl;

    if (round == 0)
    {
      int ln = lower.size();
      int un = upper.size();
      int ui = 1;
      int li = 1;
      while (ui < un && li < ln) {
        if (seg_x_seg(upper[ui], upper[ui-1], lower[li], lower[li-1])) {
          inter = line_inter(upper[ui], upper[ui-1], lower[li], lower[li-1]);
          if (inter.real() < circles[id].x) left = max(left, inter.real());
          else right = min(right, inter.real());
        }
        if (ui == un) li++;
        else if (li == ln) ui++;
        else if (upper[ui].real() < lower[li].real()) ui++;
        else li++;
      }
    }
    else
    {
      for (const pt& it : lower) {
        points.push_back(it);
      }
      for (int i = upper.size()-1; i >= 0; i--) {
        if (!eq(upper[i], points.back()) && !eq(upper[i], points.front())) {
          points.push_back(upper[i]);
        }
      }
    }
  }

  // output
  cout << points.size() << nl;
  for (const pt& it : points) {
    cout << it.real() << " " << it.imag() << nl;
  }
}

mt19937 even_more_luck(chrono::high_resolution_clock::now().time_since_epoch().count());

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(17);

  cin >> w >> h >> n;

  vector<Circle> circles;
  int x, y, r;
  for (int i=0; i<n; i++) {
    cin >> x >> y >> r;
    circles.push_back({x,y,r});
  }

  for (int i=0; i<n; i++) {
    solve(i, circles);
  }

  return 0;
}
