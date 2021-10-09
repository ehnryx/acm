//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#define FILENAME "tracing"

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

struct p3d {
  ld x, y, z;
};

ostream& operator << (ostream& os, const p3d& v) {
  return os << v.x << " " << v.y << " " << v.z;
}

ld abs(const p3d& v) { return sqrt(v.x*v.x + v.y*v.y + v.z*v.z); }
p3d operator + (const p3d& a, const p3d& b) { return {a.x+b.x, a.y+b.y, a.z+b.z}; }
p3d operator - (const p3d& a, const p3d& b) { return {a.x-b.x, a.y-b.y, a.z-b.z}; }
p3d operator * (const ld& c, const p3d& v) { return {c*v.x, c*v.y, c*v.z}; }
p3d operator * (const p3d& v, const ld& c) { return {v.x*c, v.y*c, v.z*c}; }
p3d operator / (const p3d& v, const ld& c) { return {v.x/c, v.y/c, v.z/c}; }

p3d O = {0, 0, 0};

ld dot(const p3d& a, const p3d& b) {
  return a.x*b.x + a.y*b.y + a.z*b.z;
}

p3d cross(const p3d& a, const p3d& b) {
  return {a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x};
}

p3d pl_inter(const p3d& p, const p3d& n, const p3d& a, const p3d& b) {
  return a + dot(p-a, n) / dot(n, b-a) * (b-a);
}

template <typename T>
bool eq(const T& a, const T& b) {
  return abs(a-b) < EPS;
}

void improve(p3d& ans, ld& len, const p3d& a, const p3d& b, const p3d& s, const p3d& d) {
  p3d n = cross(a-b, s-d) / abs(a-b);
  if(eq(O, n)) return;
  p3d normal = cross(b-a, n);
  normal = normal / abs(normal);
  p3d it = pl_inter(a, normal, s, d);
  ld dist = abs(it - s);
  if(dist < len && dot(b-a, it-a) > 0 && dot(a-b, it-b) > 0 && dot(d-s, it-s) > 0) {
    len = dist;
    ans = it;
  }
}


// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(10);
#ifdef ONLINE_JUDGE
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif

  p3d A, B, S, D;
  ld R;
  cin >> A.x >> A.y >> A.z;
  cin >> B.x >> B.y >> B.z;
  cin >> R;
  cin >> S.x >> S.y >> S.z;
  cin >> D.x >> D.y >> D.z;

  p3d axis = (B - A) / abs(B - A);
  p3d dir = (D - S) / abs(D - S);

  // case 1: ray parallel to cylinder axis
  if(eq(O, cross(axis, dir))) {
    p3d ait = pl_inter(A, axis, S, D);
    p3d bit = pl_inter(B, axis, S, D);
    ld alen = INF;
    ld blen = INF;
    if(abs(ait - A) <= R && dot(ait - S, dir) > 0) alen = abs(ait - S);
    if(abs(bit - B) <= R && dot(bit - S, dir) > 0) blen = abs(bit - S);
    if(min(alen, blen) > INF - 1) cout << "NONE" << nl;
    else cout << (alen < blen ? ait : bit) << nl;
  }

  // case 2: other
  else {
    p3d plane = cross(dir, axis);
    plane = plane / abs(plane);
    p3d amid = pl_inter(S, plane, A, A + plane);
    p3d bmid = pl_inter(S, plane, B, B + plane);
    assert(eq(abs(amid - A), abs(bmid - B)));
    if(abs(amid - A) > R || abs(bmid - B) > R) {
      cout << "NONE" << nl;
    } else {
      p3d horiz = cross(axis, plane);
      horiz = horiz / abs(horiz);
      ld h = abs(amid - A);
      ld len = sqrt(R*R - h*h);
      p3d atop = amid + len * horiz;
      p3d abot = amid - len * horiz;
      p3d btop = bmid + len * horiz;
      p3d bbot = bmid - len * horiz;
      ld clen = INF;
      p3d ans;
      improve(ans, clen, atop, abot, S, D);
      improve(ans, clen, btop, bbot, S, D);
      improve(ans, clen, atop, btop, S, D);
      improve(ans, clen, abot, bbot, S, D);
      if(clen > INF - 1) {
        cout << "NONE" << nl;
      } else {
        cout << ans << nl;
      }
    }
  }

  return 0;
}
