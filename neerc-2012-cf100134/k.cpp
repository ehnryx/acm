//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

const char nl = '\n';

struct Point {
  int x, y;
  Point(int _x=0, int _y=0): x(_x), y(_y) {}
  bool operator < (const Point& o) const {
    return x < o.x || (x == o.x && y < o.y);
  }
  bool operator != (const Point& o) const {
    return x != o.x || y != o.y;
  }
  bool operator == (const Point& o) const {
    return x == o.x && y == o.y;
  }
  Point operator - (const Point& o) const {
    return Point(x-o.x, y-o.y);
  }
  Point operator - () const {
    return Point(-x, -y);
  }
};

ll cp(const Point& a, const Point& b) {
  return (ll)a.x*b.y - (ll)a.y*b.x;
}

ll dp(const Point& a, const Point& b) {
  return (ll)a.x*b.x + (ll)a.y*b.y;
}

int sgn(const ll& x) {
  return x == 0 ? 0 : x<0 ? -1 : 1;
}

ll area(const vector<Point>& p) {
  int n = p.size();
  ll s = 0;
  for(int i=n-1, j=0; j<n; i=j++) {
    s += cp(p[i], p[j]);
  }
  return s;
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

vector<pair<Point,Point>> get_edges(const vector<Point>& p) {
  int n = p.size();
  vector<pair<Point,Point>> out;
  for(int i=n-1, j=0; j<n; i=j++) {
    out.emplace_back(p[i], p[j]);
  }
  return out;
}

struct Line {
  Point a, b;
  Line(const Point& u, const Point& v): a(u), b(v) {}
  bool operator < (const Line& o) const {
    int l = max(min(a.x, b.x), min(o.a.x, o.b.x));
    int r = min(max(a.x, b.x), max(o.a.x, o.b.x));
    ld x = (ld)(l+r)/2;
    ld y = eval(x);
    ld oy = o.eval(x);
    if(y != oy) return y < oy;
    if(max(a, b) != max(o.a, o.b)) return max(a, b) < max(o.a, o.b);
    return min(a, b) < min(o.a, o.b);
  }
  ld eval(const ld& x) const {
    if(a.x == b.x) {
      assert(x == a.x);
      return (ld) (a.y+b.y) / 2;
    } else {
      return (ld)(x-a.x)/(b.x-a.x) * (b.y-a.y) + a.y;
    }
  }
};

bool intersect(const Line& u, const Line& v, bool strict) {
  auto [a, b] = u;
  auto [c, d] = v;
  int r1 = sgn(cp(b-a, c-a));
  int r2 = sgn(cp(b-a, d-a));
  int r3 = sgn(cp(d-c, a-c));
  int r4 = sgn(cp(d-c, b-c));
  if(!r1 && !r2 && !r3) {
    if(strict && dp(b-a, d-c) < 0) return false;
    if(b < a) swap(a, b);
    if(d < c) swap(c, d);
    return a < d && c < b;
  } else if(a == c || a == d || b == c || b == d) {
    return false;
  } else if(!strict) {
    return r1*r2 <= 0 && r3*r4 <= 0;
  } else if(r1*r2 < 0) {
    return r3*r4 < 0 || (r3*r4 == 0 && r3+r4 > 0);
  } else if(r3*r4 < 0) {
    return r1*r2 < 0 || (r1*r2 == 0 && r1+r2 > 0);
  } else {
    return false;
  }
}

bool has_intersection(const vector<pair<Point,Point>>& segs, bool strict) {
  int n = segs.size();
  vector<pair<Point,int>> ev;
  for(int i=0; i<n; i++) {
    auto [a, b] = segs[i];
    ev.emplace_back(min(a, b), i);
    ev.emplace_back(max(a, b), i);
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

bool is_polygon(const vector<Point>& p) {
  if(p.size() < 3) return false;
  return !has_intersection(get_edges(p), false);
}

bool on_segment(const Point& a, const Point& b, const Point& v) {
  return cp(b-a, v-a) == 0 && dp(b-a, v-a) > 0 && dp(a-b, v-b) > 0;
}

bool on_boundary(const Point& v, const vector<Point>& p) {
  int n = p.size();
  bool res = false;
  for(int i=n-1, j=0; j<n; i=j++) {
    res |= (on_segment(p[i], p[j], v) || p[i] == v);
  }
  return res;
}

bool pt_in_polygon(const Point& v, const vector<Point>& p) {
  if(on_boundary(v, p)) return false;
  int n = p.size();
  ld res = 0;
  for(int i=n-1, j=0; j<n; i=j++) {
    res += atan2(cp(p[i]-v, p[j]-v), dp(p[i]-v, p[j]-v));
  }
  return abs(res) > 1;
}

bool cut_angle(const Point& a, const Point& b, const Point& v) {
  if(cp(a, b) < 0) return cut_angle(a, -a, v) || cut_angle(-b, b, v);
  return cp(a, v) > 0 && cp(v, b) > 0;
}

bool verts_intersect(const vector<Point>& a, const vector<Point>& b) {
  int n = a.size();
  int m = b.size();
  map<Point,vector<int>> verts;
  for(int i=0; i<n; i++) {
    verts[a[i]].push_back(i);
  }
  for(int i=0; i<m; i++) {
    verts[b[i]].push_back(i);
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

bool poly_intersect(const vector<Point>& a, const vector<Point>& b) {
  if(pt_in_polygon(a[0], b) || pt_in_polygon(b[0], a)) return true;
  if(verts_intersect(a, b)) return true;
  vector<pair<Point,Point>> edges = get_edges(a);
  vector<pair<Point,Point>> other = get_edges(b);
  edges.insert(edges.end(), other.begin(), other.end());
  return has_intersection(edges, true);
}

tuple<int,int,ll> get_line(const Point& u, const Point& v) {
  int a = u.y - v.y;
  int b = v.x - u.x;
  int g = abs(__gcd(a, b));
  if(a < 0 || (a == 0 && b < 0)) g = -g;
  ll c = (ll)a*u.x + (ll)b*u.y;
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

// TODO
// double-check correctness
// read limits carefully
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

  if(!is_polygon(a)) {
    cout << "Aastria is not a polygon" << nl;
  } else if(!is_polygon(b)) {
    cout << "Abstria is not a polygon" << nl;
  } else if(!is_polygon(c)) {
    cout << "Aabstria is not a polygon" << nl;
  } else if(poly_intersect(a, b)) {
    cout << "Aastria and Abstria intersect" << nl;
  } else if(!union_equal(a, b, c)) {
    cout << "The union of Aastria and Abstria is not equal to Aabstria" << nl;
  } else {
    cout << "OK" << nl;
  }

  return 0;
}
