#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef complex<ld> pt;
typedef vector<pt> pol;

const ld INF = 1e6;
const ld EPS = 1e-9;

#define nl '\n'

ld cp(const pt& a, const pt& b) { return imag(conj(a)*b); }

ld area(const pol& v) {
  pt res; ld s=0; int n=v.size();
  for (int i=n-1, j=0; j<n; i=j++) s += cp(v[i],v[j]); return s/2;
}

pt line_inter(const pt& a, const pt& b, const pt& c, const pt& d) {
  if (cp(b-a,d-c) < EPS) return pt(2*INF,0);
  return a + cp(c-a, d-c) / cp(b-a, d-c) * (b-a);
}

const ld is_query = -1e20;
struct Line {
  ld m, b;
  mutable function<const Line*()> succ;
  bool operator < (const Line& rhs) const {
    if (rhs.b != is_query) return m < rhs.m;
    const Line* s = succ();
    if (!s) return 0;
    ld x = rhs.m;
    return b - s->b < (s->m-m)*x;
  }
  Line operator - () const {
    return { -m, -b };
  }
};
struct HullUpper : public multiset<Line> {
  bool bad(iterator y) {
    auto z = next(y);
    if (y == begin()) {
      if (z==end()) return 0;
      return y->m == z->m && y->b <= z->b;
    }
    auto x = prev(y);
    if (z==end()) return y->m == x->m && y->b <= x->b;
    return (x->b-y->b)*(z->m-y->m) >= (y->b-z->b)*(y->m-x->m);
  }
  void insert_line(ld m, ld b) {
    auto y = insert({m,b});
    y->succ = [=] { return next(y) == end() ? 0 : &*next(y); };
    if (bad(y)) { erase(y); return; }
    while (next(y) != end() && bad(next(y))) erase(next(y)); 
    while (y != begin() && bad(prev(y))) erase(prev(y));
  }
  ld query(ld x) {
    auto l = *lower_bound((Line) { x, is_query });
    return l.m * x + l.b;
  }
};
struct HullLower : public multiset<Line> {
  bool bad(iterator y) {
    auto z = next(y);
    if (y == begin()) {
      if (z==end()) return 0;
      return y->m == z->m && y->b <= z->b;
    }
    auto x = prev(y);
    if (z==end()) return y->m == x->m && y->b <= x->b;
    return (x->b-y->b)*(z->m-y->m) >= (y->b-z->b)*(y->m-x->m);
  }
  void insert_line(ld m, ld b) {
    m = -m; b = -b;
    auto y = insert({m,b});
    y->succ = [=] { return next(y) == end() ? 0 : &*next(y); };
    if (bad(y)) { erase(y); return; }
    while (next(y) != end() && bad(next(y))) erase(next(y)); 
    while (y != begin() && bad(prev(y))) erase(prev(y));
  }
  ld query(ld x) {
    auto l = *lower_bound((Line) { x, is_query });
    return -(l.m * x + l.b);
  }
};

HullUpper bottom;
HullLower top;

ld maxv = INF;
ld minv = -INF;

void add_line(int x1, int y1, int x2, int y2) {
  if (x1==x2) {
    if (y1<y2) maxv = min(maxv, (ld)x1);
    else minv = max(minv, (ld)x1);
  }
  else if (x1<x2) { // bottom hull
    ld m = (ld)(y1-y2)/(x1-x2);
    bottom.insert_line(m, y1-m*x1);
  }
  else {
    ld m = (ld)(y1-y2)/(x1-x2);
    top.insert_line(m, y1-m*x1);
  }
}

pt intersect(Line a, Line b) {
  ld m1, b1, m2, b2;
  m1 = a.m; b1 = a.b;
  m2 = b.m; b2 = b.b;
  ld x = (b2-b1)/(m1-m2);
  ld y = m1*x+b1;
  return pt(x,y);
}

vector<ld> orig;

pol solve() {
  pol up, down;

  //cerr << "UP: " << nl;
  for (auto it = top.begin(); it != top.end(); it++) {
    if (it != top.begin()) {
      up.push_back(intersect(-*it, -*prev(it)));
      //cerr << up.back() << nl;
    }
  }

  //cerr << "DOWN: " << nl;
  for (auto it = bottom.begin(); it != bottom.end(); it++) {
    if (it != bottom.begin()) {
      down.push_back(intersect(*it, *prev(it)));
      //cerr << down.back() << nl;
    }
  }

  ld xmid = INF;
  for (const pt& p : up) {
    if (bottom.query(p.real()) < p.imag()) {
      xmid = p.real();
      break;
    }
  }
  if (xmid == INF) {
    for (const pt& p : down) {
      if (top.query(p.real()) > p.imag()) {
        xmid = p.real();
        break;
      }
    }
    if (xmid == INF) {
      for (const ld& p : orig) {
        if (bottom.query(p) < top.query(p)) {
          xmid = p;
          break;
        }
      }
      if (xmid == INF) {
        //cerr << "no middle found" << nl;
        return {};
      }
    }
  }

  ld left, mid, right;

  left = minv; right = xmid;
  while (right - left > EPS) {
    mid = (left+right)/2;
    if (top.query(mid) < bottom.query(mid)) {
      left = mid;
    } else {
      right = mid;
    }
  }
  minv = max(minv, mid);

  left = xmid; right = maxv;
  while (right - left > EPS) {
    mid = (left+right)/2;
    if (top.query(mid) < bottom.query(mid)) {
      right = mid;
    } else {
      left = mid;
    }
  }
  maxv = min(maxv, mid);

  if (maxv <= minv) {
    return {};
  }

  pol res;
  res.push_back(pt(minv,top.query(minv)));
  for (const pt& p : up) {
    if (p.real() > minv-EPS && p.real() < maxv+EPS) {
      res.push_back(p);
    }
  }
  res.push_back(pt(maxv,top.query(maxv)));
  res.push_back(pt(maxv,bottom.query(maxv)));
  for (int i=down.size()-1; i>=0; i--) {
    pt p = down[i];
    if (p.real() > minv-EPS && p.real() < maxv+EPS) {
      res.push_back(p);
    }
  }
  res.push_back(pt(minv,bottom.query(minv)));
  return res;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout << fixed << setprecision(10);

  int n;
  cin >> n;

  top.insert_line(INF,INF*INF);
  top.insert_line(-INF,INF*INF);
  bottom.insert_line(-INF,-INF*INF);
  bottom.insert_line(INF,-INF*INF);

  int a1,a2,b1,b2,c1,c2;
  for (int i=0; i<n; i++) {
    cin >> a1 >> a2 >> b1 >> b2 >> c1 >> c2;
    orig.push_back(a1);
    orig.push_back(b1);
    orig.push_back(c1);
    add_line(a1,a2,b1,b2);
    add_line(b1,b2,c1,c2);
    add_line(c1,c2,a1,a2);
  }

  pol p = solve();
  //cerr << "polygon" << nl; for (const pt& v : p) {
    //cerr << v << nl; }
  //cerr << nl;
  //cerr << "AREA: " << area(p) << nl << nl;

  ld ans = area(p);
  assert(ans < EPS);
  cout << max((ld)0, -ans) << nl;

  return 0;
}
