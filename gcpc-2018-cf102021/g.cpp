//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

//#define FILENAME sadcactus

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
const ll MOD = 998244353;
const ld EPS = 1e-9;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

struct p3d{ ld x,y,z;
  friend ostream& operator<< (ostream& os, const p3d& p) {
  return os << "(" << p.x << "," << p.y << "," << p.z << ")"; } };
ld abs(const p3d &v){ return sqrt(v.x*v.x + v.y*v.y + v.z*v.z); }
p3d operator+(const p3d& a, const p3d& b) {
  return {a.x+b.x,a.y+b.y,a.z+b.z}; }
p3d operator-(const p3d& a, const p3d& b) {
  return {a.x-b.x,a.y-b.y,a.z-b.z}; }
p3d operator*(const ld &s, const p3d &v){ return {s*v.x,s*v.y,s*v.z}; }
p3d operator/(const p3d&v, const ld &s){ return {v.x/s, v.y/s, v.z/s}; }
inline ld dot(const p3d &a, const p3d &b){
  return a.x*b.x + a.y*b.y + a.z*b.z; }
inline p3d cross(const p3d &a, const p3d &b){
  return {a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x}; }
// Azimuthal angle (longitude) to x-axis in interval [-pi, pi]
ld phi(const p3d& a) { return atan2(a.y, a.x); }
// Zenith angle (latitude) to the z-axis in interval [0, pi]
ld theta(const p3d& a) { return atan2(sqrt(a.x*a.x+a.y*a.y), a.z); }
inline ld dist(const p3d &s, const p3d &p) {
  return (p.x-s.x)*(p.x-s.x)+(p.y-s.y)*(p.y-s.y)+(p.z-s.z)*(p.z-s.z); }
// plane/line intersection. p - pt on plane, n - normal, a1 -> a2 : line
p3d pl_inter(const p3d &p, const p3d &n, const p3d &a1, const p3d &a2) {
  return a1 + dot(p - a1, n)/dot(n, a2 - a1)*(a2 - a1); }
// CCW rotation about arbitrary axis; tested pacnw2009D but pray anyway
p3d rotate(const p3d& p/*pt*/, const p3d& u/*axis*/, const ld& angle) {
  ld c = cos(angle), s = sin(angle), t = 1 - cos(angle);  return {
    p.x*(t*u.x*u.x + c)+p.y*(t*u.x*u.y - s*u.z)+p.z*(t*u.x*u.z + s*u.y),
    p.x*(t*u.x*u.y + s*u.z)+p.y*(t*u.y*u.y + c)+p.z*(t*u.y*u.z - s*u.x),
    p.x*(t*u.x*u.z - s*u.y)+p.y*(t*u.y*u.z + s*u.x)+p.z*(t*u.z*u.z + c)
  }; } // hash: 3f78e3

const ld R = 6371000; // meters
const ld light = 299792458; // meters / seconds
const p3d north = {0, 0, 1};
const ld PI = acos((ld)-1);

ld to_rad(ld x) {
  return x * PI / 180;
}

p3d get(ld lon, ld lat, ld r) {
  return {
    r * cos(lat) * cos(lon),
    r * cos(lat) * sin(lon),
    r * sin(lat)
  };
}

// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);
#if defined(ONLINE_JUDGE) && defined(FILENAME)
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif

  int n;
  cin >> n;

  ld lon, lat;
  cin >> lon >> lat;
  lon = to_rad(lon);
  lat = to_rad(lat);
  p3d pos = get(lon, lat, R);
  p3d pdir = pos / abs(pos);

  for(int i=0; i<n; i++) {
    ld psi, r, x;
    cin >> lon >> psi >> r >> x;
    lon = to_rad(lon);
    psi = to_rad(psi);
    r *= 1000; // to meters

    p3d start = get(lon, 0, r);
    p3d sdir = start / abs(start);
    p3d eq = cross(north, sdir);
    p3d dir = rotate(eq / abs(eq), sdir, psi);
    p3d rotn = cross(sdir, dir);
    assert(abs(abs(rotn) - 1) < EPS);
    p3d cur = rotate(start, rotn, x * 2*PI);

    p3d line = cur - pos;
    ld len = abs(line);
    if(dot(line / len, pdir) < 0) {
      cout << "no signal" << nl;
    } else {
      cout << len / light << nl;
    }
  }

  return 0;
}
