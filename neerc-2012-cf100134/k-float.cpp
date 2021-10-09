#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
//typedef complex<ld> pt;
typedef pair<int,int> Point;

struct pt {
  ld x, y;
  pt(const ld& _x=0, const ld& _y=0): x(_x), y(_y) {}
  ld real() const { return x; }
  ld imag() const { return y; }
  pt operator - () const { return pt(-x, -y); }
  pt operator - (const pt& o) const { return pt(x-o.x, y-o.y); }
  pt operator + (const pt& o) const { return pt(x+o.x, y+o.y); }
  pt operator * (const pt& o) const { return pt(x*o.x-y*o.y, x*o.y+y*o.x); }
  friend pt conj(const pt& v) { return pt(v.x, -v.y); }
  friend ld abs(const pt& v) { return sqrt(v.x*v.x + v.y*v.y); }
  friend ld real(const pt& v) { return v.x; }
  friend ld imag(const pt& v) { return v.y; }
};

const char nl = '\n';
const ld EPS = 1e-8;

ld cp(const pt& a, const pt& b) {
  return imag(conj(a) * b);
}

ld dp(const pt& a, const pt& b) {
  return real(conj(a) * b);
}

int sgn(const ld& x) {
  return abs(x)<EPS ? 0 : x<0 ? -1 : 1;
}

bool eq(const pt& a, const pt& b) {
  return abs(a-b) < EPS;
}

bool cmp_lex(const pt& a, const pt& b) {
  return a.real()<b.real()-EPS || (a.real()<b.real()+EPS && a.imag()<b.imag()-EPS);
}

bool cmp_edge(const pair<pt,pt>& a, const pair<pt,pt>& b) {
  if(cmp_lex(a.first, b.first)) return true;
  if(cmp_lex(b.first, a.first)) return false;
  return cmp_lex(a.second, b.second);
}

bool on_segment(const pt& a, const pt& b, const pt& v) {
  return abs(cp(b-a, v-a) / abs(a-b)) < EPS && dp(b-a, v-a) > 0 && dp(a-b, v-b) > 0;
}

bool on_boundary(const pt& v, const vector<pt>& p) {
  int n = p.size();
  bool res = false;
  for(int j=n-1, i=0; i<n; j=i++) {
    res |= (on_segment(p[j], p[i], v) || abs(p[i]-v) < EPS);
  }
  return res;
}

bool pt_in_polygon(const pt& v, const vector<pt>& p, bool strict) {
  if(on_boundary(v, p)) return !strict;
  int n = p.size();
  ld res = 0;
  for(int j=n-1, i=0; i<n; j=i++) {
    res += atan2(cp(p[j]-v, p[i]-v), dp(p[j]-v, p[i]-v));
  }
  return abs(res) > 1;
}

ld area(const vector<Point>& p) {
  int n = p.size();
  ld s = 0;
  for(int j=n-1, i=0; i<n; j=i++) {
    pt a(p[j].first, p[j].second);
    pt b(p[i].first, p[i].second);
    s += cp(a, b);
  }
  return s / 2;
}

vector<Point> read() {
  int n;
  cin >> n;
  vector<Point> p;
  for(int i=0; i<n; i++) {
    int x, y;
    cin >> x >> y;
    p.emplace_back(x, y);
  }
  if(area(p) < 0) {
    reverse(p.begin(), p.end());
  }
  return p;
}

vector<pt> perturb(const vector<Point>& p) {
  //static const pt rot = exp(pt(0, 1.789));
  static const pt rot(cos(1.789), sin(1.789));
  vector<pt> out(p.size());
  transform(p.begin(), p.end(), out.begin(), [=](const Point& v) {
    return pt(v.first, v.second) * rot;
  });
  return out;
}

vector<pair<pt,pt>> get_edges(const vector<pt>& p) {
  int n = p.size();
  vector<pair<pt,pt>> segs;
  for(int j=n-1, i=0; i<n; j=i++) {
    segs.emplace_back(p[j], p[i]);
    assert(abs(p[i].real() - p[j].real()) > 3*EPS);
  }
  return segs;
}

struct Line {
  ld m, b, s, t; pt u, v;
  Line(const pt& _u, const pt& _v): u(_u), v(_v) {
    s = min(u.real(), v.real());
    t = max(u.real(), v.real());
    m = (u.imag() - v.imag()) / (u.real() - v.real());
    b = u.imag() - m*u.real();
  }
  bool operator < (const Line& o) const {
    ld l = max(s, o.s);
    ld r = min(t, o.t);
    ld x = (l+r) / 2;
    ld y = eval(x);
    ld oy = o.eval(x);
    if(abs(y - oy) > EPS) return y < oy;
    if(abs(t - o.t) > EPS) return t < o.t;
    return s < o.s;
  }
  ld eval(const ld& x) const {
    return m*x + b;
  }
};

bool intersect(const Line& u, const Line& v, bool strict) {
  pt a = u.u, b = u.v, c = v.u, d = v.v;
  ld ab = abs(a-b), cd = abs(c-d);
  int s1 = sgn(cp(b-a, c-a) / ab);
  int s2 = sgn(cp(b-a, d-a) / ab);
  int s3 = sgn(cp(d-c, a-c) / cd);
  int s4 = sgn(cp(d-c, b-c) / cd);
  if(s1 == 0 && s2 == 0 && s3 == 0) {
    if(strict && dp(a-b, c-d) < 0) return false;
    if(cmp_lex(b, a)) swap(a, b);
    if(cmp_lex(d, c)) swap(c, d);
    return cmp_lex(a, d) && cmp_lex(c, b);
  } else if(eq(a, c) || eq(a, d) || eq(b, c) || eq(b, d)) {
    return false;
  } else if(!strict) {
    return s1*s2 <= 0 && s3*s4 <= 0;
  } else if(s1*s2 < 0) {
    return s3*s4 < 0 || (s3*s4 == 0 && s3+s4 > 0);
  } else if(s3*s4 < 0) {
    return s1*s2 < 0 || (s1*s2 == 0 && s1+s2 > 0);
  } else {
    return false;
  }
}

bool has_intersection(const vector<pair<pt,pt>>& segs, bool strict) {
  int n = segs.size();
  vector<pair<ld,int>> ev;
  for(int i=0; i<n; i++) {
    const auto& [a, b] = segs[i];
    ld s = min(a.real(), b.real());
    ld t = max(a.real(), b.real());
    ev.emplace_back(s, i);
    ev.emplace_back(t, i);
  }
  sort(ev.begin(), ev.end());

  vector<bool> in_set(n);
  vector<bool> skip_removal(n);
  set<Line> active;
  for(auto [_, i] : ev) {
    Line cur(segs[i].first, segs[i].second);
    if(in_set[i]) {
      if(skip_removal[i]) continue;
      auto it = active.erase(active.find(cur));
      if(it != active.begin() && it != active.end() && intersect(*it, *prev(it), strict)) {
        return true;
      }
    } else {
      in_set[i] = true;
      auto [it, ok] = active.insert(cur);
      if(!ok) {
        if(intersect(*it, cur, strict)) return true;
        skip_removal[i] = true;
      } else {
        if(it != active.begin() && intersect(*it, *prev(it), strict)) {
          return true;
        }
        if(next(it) != active.end() && intersect(*it, *next(it), strict)) {
          return true;
        }
      }
    }
  }
  return false;
}

bool is_polygon(const vector<pt>& p) {
  int n = p.size();
  if(n < 3) return false;
  return !has_intersection(get_edges(p), false);
}

bool cut_angle(const pt& a, const pt& b, const pt& v) {
  if(sgn(cp(a, b)) < 0) return cut_angle(a, -a, v) || cut_angle(-b, b, v);
  return sgn(cp(a, v)) > 0 && sgn(cp(v, b)) > 0;
}

bool verts_intersect(const vector<pt>& a, const vector<pt>& b) {
  int n = a.size();
  int m = b.size();
  map<pair<ld,ld>,vector<int>> verts;
  for(int i=0; i<n; i++) {
    pair<ld,ld> cur(a[i].real(), a[i].imag());
    verts[cur].push_back(i);
  }
  for(int i=0; i<m; i++) {
    pair<ld,ld> cur(b[i].real(), b[i].imag());
    verts[cur].push_back(i);
  }

  for(const auto& [_, v] : verts) {
    if(v.size() < 2) continue;
    int i = v[0], pi = (i+n-1)%n, ni = (i+1)%n;
    int j = v[1], pj = (j+m-1)%m, nj = (j+1)%m;
    if(cut_angle(a[ni] - a[i], a[pi] - a[i], b[pj] - b[j])) return true;
    if(cut_angle(a[ni] - a[i], a[pi] - a[i], b[nj] - b[j])) return true;
    if(cut_angle(b[nj] - b[j], b[pj] - b[j], a[pi] - a[i])) return true;
    if(cut_angle(b[nj] - b[j], b[pj] - b[j], a[ni] - a[i])) return true;
  }
  return false;
}

bool poly_intersect(const vector<pt>& a, const vector<pt>& b) {
  if(pt_in_polygon(a[0], b, true) || pt_in_polygon(b[0], a, true)) return true;
  if(verts_intersect(a, b)) return true;
  vector<pair<pt,pt>> segs = get_edges(a);
  vector<pair<pt,pt>> other = get_edges(b);
  segs.insert(segs.end(), other.begin(), other.end());
  return has_intersection(segs, true);
}

tuple<int,int,ll> get_line(const Point& u, const Point& v) {
  int a = u.second - v.second;
  int b = v.first - u.first;
  int g = abs(__gcd(a, b));
  if(a < 0 || (a == 0 && b < 0)) g = -g;
  ll c = (ll)a*u.first + (ll)b*u.second;
  return make_tuple(a/g, b/g, c/g);
}

vector<pair<Point,Point>> remove_overlap(const vector<Point>& a, const vector<Point>& b) {
  int n = a.size();
  int m = b.size();
  map<tuple<int,int,ll>,vector<pair<Point,int>>> lines;
  for(int j=n-1, i=0; i<n; j=i++) {
    tuple<int,int,ll> cur = get_line(a[i], a[j]);
    lines[cur].emplace_back(min(a[i], a[j]), -1);
    lines[cur].emplace_back(max(a[i], a[j]), 1);
  }
  for(int j=m-1, i=0; i<m; j=i++) {
    tuple<int,int,ll> cur = get_line(b[i], b[j]);
    lines[cur].emplace_back(min(b[i], b[j]), -1);
    lines[cur].emplace_back(max(b[i], b[j]), 1);
  }

  vector<pair<Point,Point>> out;
  for(auto& [_, line] : lines) {
    sort(line.begin(), line.end());
    int cur = 0;
    Point pre;
    bool first = true;
    for(const auto& [v, t] : line) {
      if(cur == -1 && pre != v) {
        if(!first && out.back().second == pre) {
          out.back().second = v;
        } else {
          out.emplace_back(pre, v);
        }
        first = false;
      }
      cur += t;
      pre = v;
    }
  }
  sort(out.begin(), out.end());
  return out;
}

bool union_equal(const vector<Point>& a, const vector<Point>& b, const vector<Point>& c) {
  vector<pair<Point,Point>> ab = remove_overlap(a, b);
  vector<pair<Point,Point>> ce = remove_overlap(c, {});
  return ab == ce;
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

#ifdef ONLINE_JUDGE
  freopen("kingdom.in", "r", stdin);
  freopen("kingdom.out", "w", stdout);
#endif

  vector<Point> a = read();
  vector<Point> b = read();
  vector<Point> c = read();
  vector<pt> ra = perturb(a);
  vector<pt> rb = perturb(b);
  vector<pt> rc = perturb(c);

  if(!is_polygon(ra)) {
    cout << "Aastria is not a polygon" << nl;
    return 0;
  }

  if(!is_polygon(rb)) {
    cout << "Abstria is not a polygon" << nl;
    return 0;
  }

  if(!is_polygon(rc)) {
    cout << "Aabstria is not a polygon" << nl;
    return 0;
  }

  if(poly_intersect(ra, rb)) {
    cout << "Aastria and Abstria intersect" << nl;
    return 0;
  }

  if(!union_equal(a, b, c)) {
    cout << "The union of Aastria and Abstria is not equal to Aabstria" << nl;
    return 0;
  }

  cout << "OK" << nl;

  return 0;
}
