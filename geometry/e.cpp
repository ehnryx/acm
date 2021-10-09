#include <bits/stdc++.h>
using namespace std;

const char nl = '\n';
typedef long double ld;
typedef complex<ld> pt;

// we can use the value of pi defined here
#define _USE_MATH_DEFINES
const ld PI = M_PIl;

// define an epsilon for floating point comparisons
const ld EPS = 1e-11;

namespace CodeArchive {
  typedef vector<pt> pol;

  // cross product
  ld cp(const pt& a, const pt& b) { return imag(conj(a)*b); }

  // comparator for complex numbers. first sorts by imaginary, then by real
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
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  // output exactly 2 digits after the decimal point
  cout << fixed << setprecision(2);

  int T;
  cin >> T;
  while (T--) {

    int n;
    cin >> n;

    vector<pt> points;
    for (int i = 0; i < n; i++) {
      int x, y;
      cin >> x >> y;
      points.push_back(pt(x, y));
    }

    // Observe that if we increase the convex hull of the points by 1 unit
    // outwards, then we will get tangents between the outermost circles.
    // If we include the arcs of the outermost circles, then we get a
    // convex curve that encloses all the circles.
    // Let P be the perimeter of the convex hull of the points, and let A
    // be the area of the convex hull of the points.
    // Now, the perimeter of the convex curve is P + 2*PI
    // and the area enclosed by the convex curve is A + P + PI
    // Don't forget to check that this (and the code below) works for
    // degerate cases like n = 1 or all points collinear

    // first find the convex hull of the points
    vector<pt> hull = CodeArchive::chull(points);

    // get the area and perimeter of the convex hull of the points
    ld A = CodeArchive::area(hull);
    ld P = 0;
    int m = hull.size();
    for (int i = 0; i < m; i++) {
      P += abs(hull[i] - hull[(i+1) % m]);
    }

    // get the area and perimeter of the convex curve that encloses all
    // the circles
    ld area = A + P + PI;
    ld perimeter = P + 2*PI;
    cout << perimeter << " " << area << nl;

  }

  return 0;
}
