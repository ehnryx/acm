#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

struct Point {
  ld x, y, z;
  Point() = default;
  Point(ld _x, ld _y, ld _z): x(_x), y(_y), z(_z) {}

  friend istream& operator >> (istream& is, Point& v) {
    return is >> v.x >> v.y >> v.z;
  }
  friend ostream& operator >> (ostream& os, const Point& v) {
    return os << v.x << v.y << v.z;
  }

  Point operator + (const Point& o) const { return Point(x+o.x, y+o.y, z+o.z); }
  Point operator - (const Point& o) const { return Point(x-o.x, y-o.y, z-o.z); }
  Point operator * (const ld& c) const { return Point(x*c, y*c, z*c); }
  Point operator / (const ld& c) const { return Point(x/c, y/c, z/c); }

  ld abs() const { return sqrt(dot(*this)); }
  ld norm() const { return dot(*this); }
  ld dot(const Point& o) const { return x*o.x + y*o.y + z*o.z; }
  Point cross(const Point& o) const {
    return Point(y*o.z - z*o.y, z*o.x - x*o.z, x*o.y - y*o.x);
  }
};

ld abs(const Point& v) { return v.abs(); }
Point cross(const Point& a, const Point& b) { return a.cross(b); }
ld dot(const Point& a, const Point& b) { return a.dot(b); }

ld lp_dist(const Point& a, const Point& b, const Point& v) {
  return abs(cross(b-a, v-a)) / abs(b-a);
}

ld lsp_dist(const Point& a, const Point& b, const Point& v) {
  if (dot(v-a, b-a) > 0 && dot(v-b, a-b) > 0) return lp_dist(a, b, v);
  return min(abs(v-a), abs(v-b));
}

ld lsls_dist(const Point& a, const Point& b, const Point& c, const Point& d, int iters=99) {
  ld l = 0;
  ld r = 1;
  for(int bs=0; bs<iters; bs++) {
    ld lm = (5*l + 4*r) / 9;
    ld rm = (4*l + 5*r) / 9;
    Point lcd = c + (d-c)*lm;
    Point rcd = c + (d-c)*rm;
    if (lsp_dist(a, b, lcd) < lsp_dist(a, b, rcd)) {
      r = rm;
    } else {
      l = lm;
    }
  }
  Point v = c + (d-c)*(l+r)/2;
  return lsp_dist(a, b, v);
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);

  Point ship, base;
  cin >> ship >> base;

  int n;
  cin >> n;

  bool ok = true;

  for(int i=0; i<n; i++) {
    Point center, dir;
    cin >> center >> dir;

    int m;
    cin >> m;
    ld radius = 0;
    for(int j=0; j<m; j++) {
      Point v;
      cin >> v;
      radius = max(radius, abs(v-center));
    }

    // do we hit the sphere?
    if (lsp_dist(ship, base, center) <= radius) {
      ok = false;
      break;
    }

    // do we hit the cylinder?
    dir = dir / abs(dir);
    if(lsls_dist(ship, base, center, center + dir * 1e7) <= radius) {
      ok = false;
      break;
    }
  }

  if (ok) {
    cout << "Go" << nl;
  } else {
    cout << "Surrender" << nl;
  }

  return 0;
}
