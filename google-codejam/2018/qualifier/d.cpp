#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;
typedef mt19937 RNG;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;

template <class T, class U>
ostream& operator << (ostream& os, const pair<T,U>& v) {
  return os << '(' << v.first << ',' << v.second << ')';
}
template <class T> 
ostream& operator << (ostream& os, const vector<T>& v) {
  for (const T& it : v) os << it << " "; return os;
}
template <class T> 
ostream& operator << (ostream& os, const set<T>& v) {
  os << "{ "; for (const T& it : v) os << it << " "; 
  return os << '}';
}
template <class T, class U> 
ostream& operator << (ostream& os, const map<T,U>& v) {
  os << "{ "; for (const pair<T,U>& it : v) os << it << " ";
  return os << '}';
}

////////////////////////////////////////////////////////////////////////

void solve();
void init() {
}
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(10);
  init();

  int T;
  cin >> T;
  for (int cc = 1; cc <= T; cc++) {
    cout << "Case #" << cc << ": ";
    solve();
  }

  return 0;
}

////////////////////////////////////////////////////////////////////////

/*
 *     |\
 *     | \
 *     |  \
 * sq2 |   \
 *     |    \
 *     |     \
 *     +-------
 *         1
 */

////////////////////////////////////////////////////////////////////////////////
// General 3D geometry
////////////////////////////////////////////////////////////////////////////////
struct p3d{ ld x,y,z; friend ostream& operator<< (ostream& os, const p3d& p) {
  return os << p.x << " " << p.y << " " << p.z; } };
ld abs(const p3d &v){ return sqrt(v.x*v.x + v.y*v.y + v.z*v.z); }
p3d operator+(const p3d&a,const p3d&b){ return {a.x+b.x,a.y+b.y,a.z+b.z}; }
p3d operator-(const p3d&a,const p3d&b){ return {a.x-b.x,a.y-b.y,a.z-b.z}; }
p3d operator*(const ld &s, const p3d &v){ return {s*v.x, s*v.y, s*v.z}; }
p3d operator/(const p3d&v, const ld &s){ return {v.x/s, v.y/s, v.z/s}; }
inline ld dot(const p3d &a, const p3d &b){ return a.x*b.x + a.y*b.y + a.z*b.z; }
inline p3d cross(const p3d &a, const p3d &b){
  return {a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x}; }
inline ld dist(const p3d &s, const p3d &p) {
  return (p.x-s.x)*(p.x-s.x) + (p.y-s.y)*(p.y-s.y) + (p.z-s.z)*(p.z-s.z); }
// plane/line intersection. p - pt on plane, n - normal, a1 -> a2 : line
inline p3d pl_inter(const p3d &p, const p3d &n, const p3d &a1, const p3d &a2){
  return a1 + dot(p - a1, n)/dot(n, a2 - a1)*(a2 - a1); }
////////////////////////////////////////////////////////////////////////////////
// CCW 3D rotation about arbitrary axis; tested on 2009 pacnw D but pray anyway
////////////////////////////////////////////////////////////////////////////////
inline p3d rotate(const p3d& p /*pt*/, const p3d& u /*axis*/, const ld& angle) {
  ld c = cos(angle), s = sin(angle), t = 1 - cos(angle);  return {
    p.x*(t*u.x*u.x + c) + p.y*(t*u.x*u.y - s*u.z) + p.z*(t*u.x*u.z + s*u.y),
    p.x*(t*u.x*u.y + s*u.z) + p.y*(t*u.y*u.y + c) + p.z*(t*u.y*u.z - s*u.x),
    p.x*(t*u.x*u.z - s*u.y) + p.y*(t*u.y*u.z + s*u.x) + p.z*(t*u.z*u.z + c) }; 
}
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// General 2D geometry, Polygon cutting, Point in polygon
////////////////////////////////////////////////////////////////////////////////
ld cp(const pt& a, const pt& b) { return imag(conj(a)*b); }
ld dp(const pt& a, const pt& b) { return real(conj(a)*b); }
// dist(const pt& a, const pt& b) ==> abs(a-b)
inline bool eq(const pt &a, const pt &b) { return abs(a-b) < EPS; }
inline ld sgn(const ld& x) { return abs(x) < EPS ? 0 : x/abs(x); }
inline bool cmp_lex(const pt& a, const pt& b) {
  return a.real()<b.real()-EPS||(a.real()<b.real()+EPS&&a.imag()<b.imag()-EPS);}
inline bool cmp_lex_i(const pt& a, const pt& b) {
  return a.imag()<b.imag()-EPS||(a.imag()<b.imag()+EPS&&a.real()<b.real()-EPS);}
// Area of a polygon (convex or concave). Always non-negative.
ld area(const pol &v) { ld s = 0; int n = v.size();
  for(int i = n-1, j = 0; j < n; i = j++) s += cp(v[i], v[j]); return abs(s)/2;}
////////////////////////////////////////////////////////////////////////////////
// 2D convex hull (TESTED SPOJ BSHEEP, UVA 11096)
////////////////////////////////////////////////////////////////////////////////
// Assumes nondegenerate, i.e. CH is not a line. 
pol chull(pol p) {
  sort(p.begin(), p.end(), cmp_lex_i); int top=0, bot=1; pol ch(2*p.size());
  for (int i=0, d=1; i < p.size() && i >= 0; i += d) {
  // If there are no duplicates, can change <= 0 to < 0 to keep redundant points
    while (top > bot && cp(ch[top-1]-ch[top-2], p[i]-ch[top-2]) <= 0) top--;
    ch[top++] = p[i]; if (i == p.size()-1) d = -1, bot = top;
  } ch.resize(max(1, top-1)); return ch; } // pts returned in ccw order.
////////////////////////////////////////////////////////////////////////////////

vector<p3d> cube1({
    {0.5L, 0.5L, 0.5L}, 
    {-0.5L, 0.5L, 0.5L},
    {0.5L, -0.5L, 0.5L},
    {0.5L, 0.5L, -0.5L},
    {-0.5L, -0.5L, 0.5L},
    {-0.5L, 0.5L, -0.5L},
    {0.5L, -0.5L, -0.5L},
    {-0.5L, -0.5L, -0.5L}});
vector<p3d> cube2;
p3d normal = {0,1,0};

void caseinit() {
  cout << nl;
  for (const p3d& p : cube1) {
    cube2.push_back(rotate(p, {1,0,0}, M_PIl/4));
  }
}

vector<p3d> get_points1(ld angle) {
  vector<p3d> res;
  for (const p3d& p : cube1) {
    res.push_back(rotate(p, {1,0,0}, angle));
  }
  return res;
}

vector<p3d> get_points2(ld angle) {
  vector<p3d> res;
  for (const p3d& p : cube2) {
    res.push_back(rotate(p, {0,0,1}, angle));
  }
  return res;
}

ld project1(ld angle) {
  vector<p3d> sphere = get_points1(angle);
  vector<pt> points;
  for (const p3d& p : sphere) {
    p3d projected = pl_inter({0,0,0}, normal, p, p + normal);
    points.push_back(pt(projected.x, projected.z));
  }
  return area(chull(points));
}

ld project2(ld angle) {
  vector<p3d> sphere = get_points2(angle);
  vector<pt> points;
  for (const p3d& p : sphere) {
    p3d projected = pl_inter({0,0,0}, normal, p, p + normal);
    points.push_back(pt(projected.x, projected.z));
  }
  return area(chull(points));
}

void getans1(ld angle) {
  vector<p3d> sphere = get_points1(angle);
  cout << (sphere[0] + sphere[1] + sphere[2] + sphere[4]) / 4 << nl;
  cout << (sphere[0] + sphere[2] + sphere[3] + sphere[6]) / 4 << nl;
  cout << (sphere[0] + sphere[1] + sphere[3] + sphere[5]) / 4 << nl;
  //cerr << "AREA: " << project1(angle) << nl;
}

void getans2(ld angle) {
  vector<p3d> sphere = get_points2(angle);
  cout << (sphere[0] + sphere[1] + sphere[2] + sphere[4]) / 4 << nl;
  cout << (sphere[0] + sphere[2] + sphere[3] + sphere[6]) / 4 << nl;
  cout << (sphere[0] + sphere[1] + sphere[3] + sphere[5]) / 4 << nl;
  //cerr << "AREA: " << project2(angle) << nl;
}

void solve() {
  caseinit();

  ld area;
  cin >> area;

  if (area > sqrt((ld)2)) {
    //cerr << "second" << nl;
    ld left, mid, right;
    left = 0;
    right = atan2(1, sqrt((ld)2));
    while (right - left > EPS) {
      mid = (left + right) / 2;
      if (project2(mid) > area) {
        right = mid;
      } else {
        left = mid;
      }
    }
    getans2(mid);
  }
  else {
    //cerr << "first" << nl;
    ld left, mid, right;
    left = 0;
    right = M_PIl/4;
    while (right - left > EPS) {
      mid = (left + right) / 2;
      if (project1(mid) > area) {
        right = mid;
      } else {
        left = mid;
      }
    }
    getans1(mid);
  }

  return;
}

