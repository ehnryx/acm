#include <bits/stdc++.h>
using namespace std;

// MAGIC IO
inline char get(void) {
  static char buf[100000], *S = buf, *T = buf;
  if (S == T) {
    T = (S = buf) + fread(buf, 1, 100000, stdin);
    if (S == T) return EOF;
  }
  return *S++;
}
template <typename T> inline void read(T &x) {
  static char c; x = 0; int sgn = 0;
  for (c = get(); c < '0' || c > '9'; c = get()) if (c == '-') sgn = 1;
  for (; c >= '0' && c <= '9'; c = get()) x = x * 10 + c - '0';
  if (sgn) x = -x;
}
void readchar(char& c) {
  while (isspace(c = get()));
}
// END MAGIC IO

typedef long long ll;
typedef double ld;

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
};

ostream& operator << (ostream& os, const Point& v) {
  return os << '(' << v.x << ',' << v.y << ')';
}

ll cp(const Point& a, const Point& b) {
  return (ll)a.x*b.y - (ll)a.y*b.x;
}

int sgn(const ll& x) {
  return x == 0 ? 0 : x<0 ? -1 : 1;
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

bool intersect(const Line& u, const Line& v) {
  auto [a, b] = u;
  auto [c, d] = v;
  int r1 = sgn(cp(b-a, c-a));
  int r2 = sgn(cp(b-a, d-a));
  int r3 = sgn(cp(d-c, a-c));
  int r4 = sgn(cp(d-c, b-c));
  if(!r1 && !r2 && !r3) {
    if(b < a) swap(a, b);
    if(d < c) swap(c, d);
    return a < d && c < b;
  } else if(a == c || a == d || b == c || b == d) {
    return false;
  } else {
    return r1*r2 <= 0 && r3*r4 <= 0;
  }
}

bool is_polygon(const vector<Point>& p) {
  int n = p.size();
  vector<pair<Point,int>> ev;
  for(int i=n-1, j=0; j<n; i=j++) {
    ev.emplace_back(min(p[i], p[j]), i);
    ev.emplace_back(max(p[i], p[j]), i);
  }
  sort(ev.begin(), ev.end());

  vector<bool> in_set(n);
  set<Line> active;
  for(auto [_, i] : ev) {
    Line cur(p[i], p[(i+1)%n]);
    if(in_set[i]) {
      auto it = active.erase(active.find(cur));
      if(it != active.begin() && it != active.end() && intersect(*it, *prev(it))) {
        return false;
      }
    } else {
      in_set[i] = true;
      auto [it, ok] = active.insert(cur);
      assert(ok);
      if(it != active.begin() && intersect(*it, *prev(it))) {
        return false;
      }
      if(next(it) != active.end() && intersect(*it, *next(it))) {
        return false;
      }
    }
  }
  return true;
}

// TODO
// double-check correctness
// read limits carefully
int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  int n;
  for(read(n); n; read(n)) {
    vector<Point> p;
    set<Point> seen;
    bool ok = true;
    for(int i=0; i<n; i++) {
      int x, y;
      read(x); read(y);
      Point cur(x, y);
      p.emplace_back(cur);
      ok &= seen.insert(cur).second;
    }
    if(ok && is_polygon(p)) {
      printf("YES\n");
    } else {
      printf("NO\n");
    }
  }

  return 0;
}
