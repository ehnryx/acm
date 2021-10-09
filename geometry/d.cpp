#include <bits/stdc++.h>
using namespace std;

const char nl = '\n';
typedef long double ld;
typedef complex<ld> pt;

// define an epsilon for floating point comparisons
const ld EPS = 1e-11;

// define PI for converting degrees to radians
const ld PI = acos((ld) -1);

namespace CodeArchive {
  typedef vector<pt> pol;

  // cross product
  ld cp(const pt& a, const pt& b) { return imag(conj(a)*b); }

  // sign of a number
  inline ld sgn(const ld& x) { return abs(x) < EPS ? 0 : (x < 0 ? -1 : 1); }

  // comparator for complex numbers, first sort by real, then by imaginary
  inline bool cmp_lex(const pt& a, const pt& b) {
  return a.real()<b.real()-EPS||(a.real()<b.real()+EPS&&a.imag()<b.imag()-EPS);}

  // checks whether two line segment intersect
  // handles ALL cases, uncomment/edit the 3 marked lines to exclude endpoints
  bool seg_x_seg(pt a1, pt a2, pt b1, pt b2) {
    //if (eq(a1,a2) || eq(b1,b2)) return false; // uncomment to exclude endpoints
    ld za = abs(a2-a1), zb = abs(b2-b1); za=za>EPS?1/za:0; zb=zb>EPS?1/zb:0;
    int s1 = sgn(cp(a2-a1, b1-a1)*za), s2 = sgn(cp(a2-a1, b2-a1)*za);
    int s3 = sgn(cp(b2-b1, a1-b1)*zb), s4 = sgn(cp(b2-b1, a2-b1)*zb);
    if(!s1 && !s2 && !s3) { // collinear
      if (cmp_lex(a2, a1)) swap(a1, a2); if (cmp_lex(b2, b1)) swap(b1, b2);
      //return cmp_lex(a1, b2) && cmp_lex(b1, a2);//uncomment to exclude endpoints
      return !cmp_lex(b2, a1) && !cmp_lex(a2, b1);
    } return s1*s2 <= 0 && s3*s4 <= 0; } //change to < to exclude endpoints
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int T;
  cin >> T;
  while (T--) {

    int n;
    cin >> n;

    // We simulate Daniel, and keep track of the path that he has travelled.
    // First put Daniel at (0,0)
    pt cur(0, 0);
    // Suppose that Daniel is facing in the direction (1,0)
    // We should make sure that dir has magnitude 1 for easier calculations later
    pt dir(1, 0);

    int fall = 0;
    vector<pt> points;
    for (int i = 1; i <= n; i++) {
      int a, d;
      cin >> a >> d;

      // skip the calculations if Daniel has already fallen
      if (fall) {
        continue;
      }

      // find the new direction and where daniel will end up
      ld rad = (ld) a * PI / 180;    // convert a to radians
      dir *= exp(pt(0, rad));        // rotation by rad is multiplication by e^(i rad)
      pt dest = cur + (ld) d * dir;  // get the next point that Daniel walks to

      // Check whether the current move intersects any previous line segment
      // We should exclude the segment that ends at Daniel's current point because
      // we know that the next segment will not intersect that one other than at Daniel's
      // current point (he can't make 180 degree turns)
      for (int j = 1; j < points.size(); j++) {
        if (CodeArchive::seg_x_seg(points[j], points[j-1], cur, dest)) {
          // Daniel walks into the water, but we shouldn't continue in the outer loop
          // because we need to finish reading the input
          fall = i;
          break;
        }
      }

      points.push_back(cur);  // push Daniel's old position to the list of points
      cur = dest;             // update his new position
    }

    if (fall) {
      cout << fall << nl;
    } else {
      cout << "SAFE" << nl;
    }

  }

  return 0;
}
