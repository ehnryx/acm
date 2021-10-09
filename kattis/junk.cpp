//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;
typedef long double ld;
typedef complex<ld> pt;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-13;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

ld sqr(const ld& x) {
  return x*x;
}

struct p3d {
  ld x,y,z;
  p3d operator + (const p3d& o) const {
    return { x+o.x, y+o.y, z+o.z };
  }
  p3d operator - (const p3d& o) const {
    return { x-o.x, y-o.y, z-o.z };
  }
  p3d operator / (const ld& c) const {
    return { x/c, y/c, z/c };
  }
  friend p3d operator * (const ld& c, const p3d& p) {
    return { c*p.x, c*p.y, c*p.z };
  }
  ld norm() const {
    return sqr(x) + sqr(y) + sqr(z);
  }
  ld norm(const p3d& o) const {
    return sqr(x-o.x) + sqr(y-o.y) + sqr(z-o.z);
  }
};

ld dot(const p3d& a, const p3d& b) {
  return a.x*b.x + a.y*b.y + a.z*b.z;
}

p3d pl_inter(const p3d &p, const p3d &n, const p3d &a1, const p3d &a2) {
  return a1 + dot(p-a1, n) / dot(n, a2-a1) * (a2 - a1);
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);

  int T;
  cin >> T;
  while(T--) {
    int x, y, z, r, vx, vy, vz;
    cin >> x >> y >> z >> r >> vx >> vy >> vz;
    int x2, y2, z2, r2, vx2, vy2, vz2;
    cin >> x2 >> y2 >> z2 >> r2 >> vx2 >> vy2 >> vz2;
    x -= x2;
    y -= y2;
    z -= z2;
    vx -= vx2;
    vy -= vy2;
    vz -= vz2;
    r += r2;
    p3d o = {0, 0, 0};
    p3d s = {x, y, z};
    p3d dir = {vx, vy, vz};
    ld v = sqrt(dir.norm());
    if(v < 0.1) {
      cout << "No collision" << nl;
      continue;
    }
    dir = dir / v;
    p3d it = pl_inter(o, dir, s, s+dir);
    if(dot(it-s, dir) < 0) {
      cout << "No collision" << nl;
    } else {
      ld p = o.norm(it);
      if(p > r*r) {
        cout << "No collision" << nl;
      } else {
        ld m = sqrt(r*r - p);
        ld d = sqrt(s.norm(it));
        cout << (d - m) / v << nl;
      }
    }
  }

  return 0;
}
