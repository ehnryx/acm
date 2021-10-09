#pragma GCC optimize("O3")
#pragma GCC target("sse4,avx2,abm,fma,tune=native")
#include <bits/stdc++.h>
using namespace std;

template <class T> ostream& operator << (ostream& os, const vector<T>& v) {
  os << "[";
  for(const T& it : v) {
    os << " " << it << ", ";
  }
  return os << "]";
}

const char nl = '\n';
typedef double ld;
const ld PI = acos((ld)-1);
const ld EPS = 1e-8;
const ld VERY_SMALL = 1e-13;

ld sqr(const ld& x) {
  return x*x;
}

struct p3d {
  ld x, y, z;
  p3d(const ld& _x=0, const ld& _y=0, const ld& _z=0): x(_x), y(_y), z(_z) {}
  friend ostream& operator << (ostream& os, const p3d& v) {
    return os << "(" << v.x << "," << v.y << "," << v.z << ")";
  }
  p3d operator - () const { return p3d(-x, -y, -z); }
  p3d operator + (const p3d& o) const { return p3d(x+o.x, y+o.y, z+o.z); }
  p3d operator - (const p3d& o) const { return p3d(x-o.x, y-o.y, z-o.z); }
  p3d operator * (const ld& c) const { return p3d(x*c, y*c, z*c); }
  p3d operator / (const ld& c) const { return p3d(x/c, y/c, z/c); }
  friend p3d operator * (const ld& c, const p3d& v) { return v * c; }
};

p3d cross(const p3d& a, const p3d& b) {
  return p3d(a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x);
}

ld dot(const p3d& a, const p3d& b) {
  return a.x*b.x + a.y*b.y + a.z*b.z;
}

ld abs(const p3d& a) {
  return sqrt(dot(a, a));
}

ld norm(const p3d& a) {
  return dot(a, a);
}

p3d flatten(const p3d& a) {
  return p3d(a.x, a.y, 0);
}

template <class T>
bool eq(const T& a, const T& b) {
  return abs(a-b) < EPS;
}

p3d pl_inter(const p3d& p, const p3d& n, const p3d& a, const p3d& b) {
  return a + dot(p-a, n) / dot(n, b-a) * (b-a);
}

p3d rotate(const p3d& p, const p3d& u, const ld& angle) {
  ld c = cos(angle), s = sin(angle), t = 1 - cos(angle);
  return {
    p.x * (t*u.x*u.x + c) + p.y * (t*u.x*u.y - s*u.z) + p.z * (t*u.x*u.z + s*u.y),
    p.x * (t*u.x*u.y + s*u.z) + p.y * (t*u.y*u.y + c) + p.z * (t*u.y*u.z - s*u.x),
    p.x * (t*u.x*u.z - s*u.y) + p.y * (t*u.y*u.z + s*u.x) + p.z * (t*u.z*u.z + c),
  };
}

bool on_segment(const p3d& a, const p3d& b, const p3d& v) {
  return abs(cross(b-a, v-a)) / abs(b-a) < EPS && dot(b-a, v-a) > 0 && dot(a-b, v-b) > 0;
}

bool on_boundary(const vector<p3d>& p, const p3d& v) {
  int m = p.size();
  bool res = false;
  for(int i=m-1, j=0; j<m; i=j++) {
    res |= (on_segment(p[i], p[j], v) || eq(p[i], v));
  }
  return res;
}

bool pt_in_polygon(const vector<p3d>& p, const p3d& v) {
  //if(on_boundary(p, v)) return true;
  p3d n = cross(p[1]-p[0], p[2]-p[0]);
  n = n / abs(n);
  int m = p.size();
  ld res = 0;
  for(int i=m-1, j=0; j<m; i=j++) {
    res += atan2(dot(cross(p[i]-v, p[j]-v), n), dot(p[i]-v, p[j]-v));
  }
  return abs(res) > 1;
}

const ld BIG = 2e7 + 7;

enum {
  CUBE,
  SPHERE,
  TETRA,
};

const p3d UP(0, 0, 1);

struct Polyhedron;
struct Sphere;

struct Polyhedron {
  ld top, bottom, to_bottom;
  vector<p3d> verts;
  vector<pair<p3d,p3d>> edges;
  vector<vector<p3d>> faces;

  void init(int a, int b, int c, int x, int y) {
    p3d X(1, 0, 0), Z(0, 0, 1);
    rotate_self(Z, (ld)a*PI/180);
    X = rotate(X, Z, (ld)a*PI/180);
    rotate_self(X, (ld)b*PI/180);
    Z = rotate(Z, X, (ld)b*PI/180);
    rotate_self(Z, (ld)c*PI/180);
    move_by(p3d(x, y, 0));
    to_bottom = 0;
    for(const p3d& v : verts) {
      to_bottom = max(to_bottom, -v.z);
    }
  }

  void rotate_self(const p3d& u, const ld& r) {
    for(p3d& v : verts) {
      v = rotate(v, u, r);
    }
    for(pair<p3d,p3d>& e : edges) {
      e.first = rotate(e.first, u, r);
      e.second = rotate(e.second, u, r);
    }
    for(vector<p3d>& f : faces) {
      for(p3d& v : f) {
        v = rotate(v, u, r);
      }
    }
  }

  void move_by(const p3d& t) {
    top = 0;
    bottom = BIG;
    for(p3d& v : verts) {
      v = v + t;
      top = max(top, v.z);
      bottom = min(bottom, v.z);
    }
    for(pair<p3d,p3d>& e : edges) {
      e.first = e.first + t;
      e.second = e.second + t;
    }
    for(vector<p3d>& f : faces) {
      for(p3d& v : f) {
        v = v + t;
      }
    }
  }

  Polyhedron operator - () const {
    Polyhedron res = *this;
    res.top = -bottom;
    res.bottom = -top;
    for(p3d& v : res.verts) {
      v = -v;
    }
    for(pair<p3d,p3d>& e : res.edges) {
      e.first = -e.first;
      e.second = -e.second;
    }
    for(vector<p3d>& f : res.faces) {
      for(p3d& v : f) {
        v = -v;
      }
      reverse(f.begin(), f.end());
    }
    return res;
  }

  ld distance(const Polyhedron& o, const ld& best) const {
    if(bottom - o.top > best) return BIG;
    ld dist = best;
    for(const auto& [a, b] : edges) {
      for(const auto& [c, d] : o.edges) {
        if(min(a.z, b.z) - max(c.z, d.z) > dist) continue;
        dist = min(dist, distance(a, b, c, d));
      }
    }
    for(const auto& f : o.faces) {
      for(const auto& v : verts) {
        dist = min(dist, distance(v, f));
      }
    }
    for(const auto& f : faces) {
      if(cross(f[1]-f[0], f[2]-f[0]).z > -EPS) continue;
      for(const auto& v : o.verts) {
        dist = min(dist, distance(v, f));
      }
    }
    return dist;
  }

  ld distance(const p3d& a, const p3d& b, const p3d& u, const p3d& v) const {
    if(eq(flatten(a), flatten(b)) || eq(flatten(u), flatten(v))) return BIG;
    p3d n = cross(v - u, UP);
    n = n / abs(n);
    if(abs(dot(n, b-a)) < EPS) return BIG;
    p3d contact = pl_inter(u, n, a, b);
    if(!on_segment(a, b, contact)) return BIG;
    p3d pn = cross(v - u, n) / abs(v - u);
    p3d hit = pl_inter(u, pn, contact, contact + UP);
    if(!on_segment(u, v, hit)) return BIG;
    return abs(hit - contact);
  }

  ld distance(const p3d& v, const vector<p3d>& f) const {
    p3d n = cross(f[1]-f[0], f[2]-f[0]);
    n = n / abs(n);
    if(abs(n.z) < EPS) return BIG;
    p3d hit = pl_inter(f[0], n, v, v+UP);
    if(!pt_in_polygon(f, hit)) return BIG;
    return abs(hit - v);
  }

  void remove_hidden() {
    vector<vector<p3d>> upward_faces, downward_faces;
    for(const vector<p3d>& f : faces) {
      if(cross(f[1]-f[0], f[2]-f[0]).z > EPS) {
        upward_faces.push_back(f);
      } else {
        downward_faces.push_back(f);
      }
    }
    vector<pair<p3d,p3d>> upward_edges;
    for(const pair<p3d,p3d>& e : edges) {
      int cnt = 0;
      for(vector<p3d>& f : downward_faces) {
        int m = f.size();
        for(int i=m-1, j=0; j<m; i=j++) {
          cnt += (eq(e.first, f[i]) && eq(e.second, f[j]));
          cnt += (eq(e.second, f[i]) && eq(e.first, f[j]));
        }
      }
      if(cnt < 2) {
        upward_edges.push_back(e);
      }
    }
    faces = upward_faces;
    edges = upward_edges;
  }
};

struct Sphere {
  p3d center;
  ld r;
  Sphere(int x, int y, int _r): center(x, y), r(_r) {}

  Sphere operator - () const {
    Sphere res = *this;
    res.center = -center;
    return res;
  }

  ld distance(const Sphere& o) const {
    return distance(o.center, r + o.r);
  }

  ld distance(const Polyhedron& o, const ld& best) const {
    if(center.z - r - o.top > best) return BIG;
    ld dist = best;
    for(const p3d& v : o.verts) {
      if(center.z - r - v.z > dist) continue;
      dist = min(dist, distance(v, r));
    }
    for(const auto& [u, v] : o.edges) {
      if(center.z - r - max(u.z, v.z) > dist) continue;
      dist = min(dist, distance(u, v));
    }
    for(const vector<p3d>& f : o.faces) {
      dist = min(dist, distance(f));
    }
    return dist;
  }

  ld distance(const p3d& u, const p3d& v) const {
    if(eq(flatten(u), flatten(v))) return BIG;
    p3d n = cross(v - u, UP);
    n = n / abs(n);
    p3d proj = pl_inter(u, n, center, center+n);
    ld d2 = norm(proj - center);
    if(d2 > sqr(r)) return BIG;
    ld pr = sqrt(sqr(r) - d2);
    p3d pn = cross(v - u, n) / abs(v - u);
    if(pn.z < 0) pn = -pn; // make pn point upwards
    p3d contact = proj - pr * pn;
    p3d hit = pl_inter(u, pn, contact, contact + UP);
    if(!on_segment(u, v, hit)) return BIG;
    return abs(hit - contact);
  }

  ld distance(const vector<p3d>& f) const {
    p3d n = cross(f[1]-f[0], f[2]-f[0]);
    n = n / abs(n);
    if(abs(n.z) < EPS) return BIG;
    if(n.z < 0) n = -n; // make n point upwards
    p3d contact = center - r * n;
    p3d hit = pl_inter(f[0], n, contact, contact+UP);
    if(!pt_in_polygon(f, hit)) return BIG;
    return abs(hit - contact);
  }

  ld distance(const p3d& v, ld radius) const {
    ld d2 = norm(flatten(center) - flatten(v));
    if(d2 > sqr(radius)) return BIG;
    ld h = sqrt(sqr(radius) - d2);
    return abs(center.z - v.z) - h;
  }
};

Polyhedron read_cube() {
  int a, b, c, x, y, r;
  cin >> a >> b >> c >> x >> y >> r;
  ld s = (ld)r/2 + VERY_SMALL;
  p3d A(s, s, s), B(-s, s, s), C(-s, -s, s), D(s, -s, s);
  p3d E(s, s, -s), F(-s, s, -s), G(-s, -s, -s), H(s, -s, -s);
  Polyhedron res;
  res.verts = { A, B, C, D, E, F, G, H };
  res.edges = {
    {A, B}, {B, C}, {C, D}, {D, A},
    {E, F}, {F, G}, {G, H}, {H, E},
    {A, E}, {B, F}, {C, G}, {D, H},
  };
  res.faces = {
    {A, B, C, D}, {H, G, F, E},
    {A, D, H, E}, {C, B, F, G},
    {B, A, E, F}, {D, C, G, H},
  };
  res.init(a, b, c, x, y);
  return res;
}

Polyhedron read_tetra() {
  int a, b, c, x, y, r;
  cin >> a >> b >> c >> x >> y >> r;
  ld h = sqrt((ld)2/3) / 4 * r + VERY_SMALL;
  ld k = 1 / sqrt((ld)3) * r + VERY_SMALL;
  p3d A(0, 0, 3*h), B(k, 0, -h), C(-k/2, (ld)r/2, -h), D(-k/2, (ld)-r/2, -h);
  Polyhedron res;
  res.verts = { A, B, C, D };
  res.edges = { {A, B}, {A, C}, {A, D}, {B, C}, {B, D}, {C, D} };
  res.faces = { {A, B, C}, {A, C, D}, {A, D, B}, {D, C, B} };
  res.init(a, b, c, x, y);
  return res;
}

Sphere read_sphere() {
  int a, b, c, x, y, r;
  cin >> a >> b >> c >> x >> y >> r;
  return Sphere(x, y, r);
}

void solve_case() {
  int n;
  cin >> n;
  vector<Sphere> spheres;
  vector<Polyhedron> poly;
  for(int i=0; i<n; i++) {
    int t;
    cin >> t;
    if(t == SPHERE) {
      Sphere cur = read_sphere();
      cur.center.z = BIG;
      ld dist = cur.center.z - cur.r;
      for(int j=(int)spheres.size()-1; j>=0; j--) {
        dist = min(dist, cur.distance(spheres[j]));
      }
      for(int j=(int)poly.size()-1; j>=0; j--) {
        dist = min(dist, cur.distance(poly[j], dist));
      }
      cur.center.z -= dist;
      cout << cur.center.z + cur.r << nl;
      spheres.push_back(cur);
    } else {
      Polyhedron cur = (t == CUBE ? read_cube() : read_tetra());
      ld dist = BIG - cur.to_bottom;
      cur.move_by(p3d(0, 0, BIG));
      Polyhedron neg = -cur;
      for(int j=(int)spheres.size()-1; j>=0; j--) {
        dist = min(dist, (-spheres[j]).distance(neg, dist));
      }
      for(int j=(int)poly.size()-1; j>=0; j--) {
        dist = min(dist, cur.distance(poly[j], dist));
      }
      cur.move_by(p3d(0, 0, -dist));
      cout << cur.top << nl;
      cur.remove_hidden();
      poly.push_back(cur);
    }
  }
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(15);

  int T;
  cin >> T;
  while(T--) {
    solve_case();
  }

  return 0;
}
