#include <bits/stdc++.h>
using namespace std;

const char nl = '\n';
typedef long double ld;
typedef complex<ld> pt;

// define an epsilon for floating point comparisons
const ld EPS = 1e-11;

namespace CodeArchive {
  typedef vector<pt> pol;

  // cross product
  ld cp(const pt& a, const pt& b) { return imag(conj(a)*b); }
  ld dp(const pt& a, const pt& b) { return real(conj(a)*b); }

  // sign of a number
  inline ld sgn(const ld& x) { return abs(x) < EPS ? 0 : (x < 0 ? -1 : 1); }

  // line point distance
  // SIGNED distance. Pt on the right of vector (a -> b) will be NEGATIVE.
  inline ld lp_dist(const pt &a, const pt &b, const pt &p) {
    return cp(b - a, p - a) / abs(b - a); }

  // Does NOT include points on the ends of the segment.
  inline bool on_segment(const pt &a, const pt &b, const pt &p) {
    return abs(cp(b-a, p-a)) < EPS && dp(b-a, p-a) > 0 && dp(a-b, p-b) > 0; }
}

// use Barycentric Coordinates to get circumcenter of three points
pt circumcenter(const pt& A, const pt& B, const pt& C) {
  ld a2 = norm(B-C);
  ld b2 = norm(C-A);
  ld c2 = norm(A-B);
  ld fa = a2 * (b2+c2-a2);
  ld fb = b2 * (c2+a2-b2);
  ld fc = c2 * (a2+b2-c2);
  ld fn = fa + fb + fc;
  return (fa*A + fb*B + fc*C) / fn;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  // output exactly 12 digits after the decimal point
  cout << fixed << setprecision(12);

  int T;
  cin >> T;
  while (T--) {

    int n, m;
    cin >> n >> m;

    vector<pt> cover;
    for (int i = 0; i < n; i++) {
      int x, y;
      cin >> x >> y;
      cover.push_back(pt(x, y));
    }

    vector<pt> avoid;
    for (int i = 0; i < m; i++) {
      int x, y;
      cin >> x >> y;
      avoid.push_back(pt(x, y));
    }

    // if there are no points we need to cover, draw a circle arbitrarily.
    // if there is one point we need to cover, draw a circle around it.
    // in both cases, we can have radius 0
    if (cover.size() <= 1) {
      cout << 0 << nl;
      continue;
    }

    // Observe that the smallest valid disk must have at least three points
    // from the input on its boundary, and that two of these must be covered,
    // otherwise we can shrink the disk.
    // Now, we get an idea for the solution:
    // for each pair of good points, go over all other points and keep track
    // of an interval where the circumcenters of valid circles live.

    const ld BIG = 1e20;
    ld ans = BIG;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < i; j++) {
        // get the two points that are on the boundary, and their midpoint
        const pt& a = cover[i];
        const pt& b = cover[j];
        pt mid = (a + b) / (ld) 2;
        // init left and right bounds of the interval
        ld left = -BIG;
        ld right = BIG;

        // go over the other points that should be covered
        for (int k = 0; k < n; k++) {
          if (k == i || k == j) continue;
          ld distToLine = CodeArchive::lp_dist(a, b, cover[k]);
          int s = CodeArchive::sgn(distToLine);
          if (s == 0) {
            // the point is on the same line as a and b, it must be on
            // the line segment between them for this to be valid
            if (!CodeArchive::on_segment(a, b, cover[k])) {
              left = BIG;
              right = -BIG;
              break;
            }
          } else {
            // update left / right based on the position of the cover[k]
            // with respect to the line ab
            pt c = circumcenter(a, b, cover[k]);
            if (s < 0) {
              right = min(right, CodeArchive::lp_dist(a, b, c));
            } else {
              left = max(left, CodeArchive::lp_dist(a, b, c));
            }
          }
        }

        // go over the points that should be avoided
        for (int k = 0; k < m; k++) {
          ld distToLine = CodeArchive::lp_dist(a, b, avoid[k]);
          int s = CodeArchive::sgn(distToLine);
          if (s == 0) {
            // the point is on the same line as a and b, it must not
            // be on the line segment between them for this to be valid
            if (CodeArchive::on_segment(a, b, avoid[k])) {
              left = BIG;
              right = -BIG;
              break;
            }
          } else {
            // update left / right based on the position of the avoid[k]
            // with respect to the line ab
            pt c = circumcenter(a, b, avoid[k]);
            // we want to avoid these points, so decrease the interval by eps
            if (s < 0) {
              left = max(left, CodeArchive::lp_dist(a, b, c) + EPS);
            } else {
              right = min(right, CodeArchive::lp_dist(a, b, c) - EPS);
            }
          }
        }

        // update the answer
        if (left <= right) {
          pt dir = (a - b) * pt(0, 1) / abs(a - b);
          if (left > 0) {
            pt c = mid + dir * left;
            ans = min(ans, abs(c - a));
          } else if (right < 0) {
            pt c = mid + dir * right;
            ans = min(ans, abs(c - a));
          } else {
            ans = min(ans, abs(mid - a));
          }
        }
      }
    }

    if (ans < BIG/2) {
      cout << ans << nl;
    } else {
      cout << "Impossible" << nl;
    }

  }

  return 0;
}
