#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = /*long*/ double;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

constexpr ld PI = M_PIl;

namespace ubc{
using pol = vector<pt>;

ld cp(const pt& a, const pt& b) { return imag(conj(a)*b); }
ld dp(const pt& a, const pt& b) { return real(conj(a)*b); }
// dist(const pt& a, const pt& b) ==> abs(a-b)
bool eq(const pt &a, const pt &b) { return abs(a-b) < EPS; }
int sgn(const ld& x) { return abs(x) < EPS ? 0 : x < 0 ? -1 : 1; }
bool cmp_lex(const pt& a, const pt& b) {
  return a.real()<b.real()-EPS
    ||  (a.real()<=b.real()+EPS && a.imag()<b.imag()-EPS); }
inline bool cmp_lex_i(const pt& a, const pt& b) {
  return a.imag()<b.imag()-EPS
    ||  (a.imag()<=b.imag()+EPS && a.real()<b.real()-EPS); }

// handles ALL cases, uncomment the 3 marked lines to exclude endpoints
bool seg_x_seg(pt a, pt b, pt c, pt d) {
  if(eq(a, b) || eq(c, d)) return 0; // exclude endpoints
  ld sa=abs(b-a), sc=abs(d-c); sa=sa>EPS?1/sa:0; sc=sc>EPS?1/sc:0;
  int r1 = sgn(cp(b-a, c-a) * sa), r2 = sgn(cp(b-a, d-a) * sa);
  int r3 = sgn(cp(d-c, a-c) * sc), r4 = sgn(cp(d-c, b-c) * sc);
  if(!r1 && !r2 && !r3) { // collinear
    if(cmp_lex(b, a)) swap(a, b);
    if(cmp_lex(d, c)) swap(c, d);
    return cmp_lex(a, d) && cmp_lex(c, b); // exclude endpoints
    //return !cmp_lex(d, a) && !cmp_lex(b, c);
  } return r1*r2 < 0 && r3*r4 < 0; }//change to < to exclude endpoints

// Does NOT include points on the ends of the segment.
inline bool on_segment(const pt &a, const pt &b, const pt &p) {
  return abs(cp(b-a, p-a)) / abs(a-b) < EPS &&
    dp(b-a, p-a)>0 && dp(a-b, p-b)>0; }

// Checks if p lies on the boundary of a polygon v.
inline bool on_boundary(const pol &v, const pt &p) {
  bool res = 0; for(int i=v.size()-1, j=0; j<v.size(); i=j++) {
    res |= on_segment(v[i], v[j], p) || abs(p-v[i]) < EPS; }
  return res; }

// orientation does not matter !!!
bool pt_in_polygon(const pt &p, const pol &v, bool strict=false) {
  if (on_boundary(v,p)) return !strict;
  ld res = 0; for(int i = v.size() - 1, j = 0; j < v.size(); i = j++) {
    res += atan2(cp(v[i] - p, v[j] - p), dp(v[i] - p, v[j] - p)); }
  return abs(res) > 1; } // will be either 2*PI or 0
}

bool check(const vector<pt>& u, const vector<pt>& v) {
  bool ok = true;
  int n = u.size();
  int m = v.size();
  for(int i=n-1, j=0; j<n; i=j++) {
    ok &= ubc::pt_in_polygon(u[i], v);
    ok &= ubc::pt_in_polygon((u[i] + u[j]) / (ld)2, v);
    for(int ii=m-1, jj=0; jj<m; ii=jj++) {
      ok &= !ubc::seg_x_seg(u[i], u[j], v[ii], v[jj]);
    }
  }
  return ok;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);

  int n, m;
  cin >> n >> m;
  vector<pt> v, u;
  for(int i=0; i<n; i++) {
    ld x, y;
    cin >> x >> y;
    u.emplace_back(x, y);
  }
  for(int i=0; i<m; i++) {
    ld x, y;
    cin >> x >> y;
    v.emplace_back(x, y);
  }

  for(int rot=0; rot<360; rot++) {
    ld angle = (ld)rot / 180 * PI;
    vector<pt> rotu;
    for(auto x : u) {
      rotu.push_back(x * exp(pt(0, angle)));
    }
    if(check(rotu, v)) {
      cout << rot << nl;
      return 0;
    }
  }

  cout << "impossible" << nl;

  return 0;
}
