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

  // dot product
  ld dp(const pt& a, const pt& b) { return real(conj(a)*b); }

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

  // Line segment (a, b) to pt p distance.
  inline ld lsp_dist(const pt &a, const pt &b, const pt &p) {
    return dp(b - a, p - a) > 0 && dp(a - b, p - b) > 0 ?
      abs(cp(b - a, p - a) / abs(b - a)) : min(abs(a - p), abs(b - p)); }

  // checks whether a point lies in the interior of a segment
  // Does NOT include points on the ends of the segment.
  inline bool on_segment(const pt &a, const pt &b, const pt &p) {
    return abs(cp(b-a, p-a)) < EPS && dp(b-a, p-a) > 0 && dp(a-b, p-b) > 0; }

  // Checks if p lies on the boundary of a polygon v.
  inline bool on_boundary(const pol &v, const pt &p) { bool res = false;
    for(int i=v.size()-1,j=0;j<v.size();i=j++)
      res |= on_segment(v[i], v[j], p) | (abs(p-v[i]) < EPS); return res; }

  // checks whether a point lies in the interior or boundary of a polygon
  // orientation does not matter !!!
  bool pt_in_polygon(const pt &p, const pol &v){ if(on_boundary(v,p)) return true;
    ld res = 0; for(int i = v.size() - 1, j = 0; j < v.size(); i = j++)
      res += atan2(cp(v[i] - p, v[j] - p), dp(v[i] - p, v[j] - p));
    return abs(res) > 1; } // will be either 2*PI or 0
}


int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  // output exactly 2 digits after the decimal point
  cout << fixed << setprecision(2);

  // declare the distance array here to avoid allocating this for every test case
  const int N = 102;
  ld dist[N][N];

  int T;
  cin >> T;
  while (T--) {

    int width, n;
    cin >> width >> n;

    int numV[n];      // the number of points for each polygon
    vector<pt> p[n];  // the points for each polygon in order

    for (int i = 0; i < n; i++) {
      cin >> numV[i];
      for (int j = 0; j < numV[i]; j++) {
        int x, y;
        cin >> x >> y;
        p[i].push_back(pt(x, y));
      }
    }

    // first, see how far Daniel is from the polygons,
    // this gives an upper bound on his radius
    ld maxRadius = (ld) width / 2;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < numV[i]; j++) {
        ld distToSegment = CodeArchive::lsp_dist(p[i][j], p[i][(j + 1) % numV[i]], pt(0, 0));
        maxRadius = min(maxRadius, distToSegment);
      }
    }

    // second, we treat each debris and each wall as a node in a complete graph,
    // where the distance between two nodes is the shortest distance between their
    // boundaries. Then, Daniel's radius can't be greater than the largest edge on
    // a path between the two walls that minimizes the largest edge.
    const int TOP = n;
    const int BOTTOM = n + 1;
    dist[TOP][BOTTOM] = dist[BOTTOM][TOP] = width;  // distance between the two walls
    ld top_y = (ld) width / 2;
    ld bottom_y = (ld) -width / 2;

    for (int i = 0; i < n; i++) {
      // distance from a node to itself is 0
      dist[i][i] = 0;

      // find distance between debris i and j
      for (int j = 0; j < i; j++) {
        ld shortestDist = width;
        for (int it = 0; it < numV[i] && shortestDist > 0; it++) {
          int nit = (it + 1) % numV[i];  // get the next vertex on polygon i
          for (int jt = 0; jt < numV[j] && shortestDist > 0; jt++) {
            int njt = (jt + 1) % numV[j];  // get the next vertex on polygon j
            // check whether these two edges intersect
            if (CodeArchive::seg_x_seg(p[i][it], p[i][nit], p[j][jt], p[j][njt])) {
              shortestDist = 0;
              break;
            }
            // find the shortest line segment to point distance
            ld distToSegment_i = CodeArchive::lsp_dist(p[i][it], p[i][nit], p[j][jt]);
            ld distToSegment_j = CodeArchive::lsp_dist(p[j][jt], p[j][njt], p[i][it]);
            shortestDist = min(shortestDist, min(distToSegment_i, distToSegment_j));
          }
        }

        // now we know that the polygons don't intersect, but it is possible
        // that one contains the other, so we should check whether an aritrary
        // vertex of i lies in j, or vice versa
        if (CodeArchive::pt_in_polygon(p[i][0], p[j]) || CodeArchive::pt_in_polygon(p[j][0], p[i])) {
          shortestDist = 0;
        }

        // update the distance of the edge between i and j
        dist[i][j] = dist[j][i] = shortestDist;
      }

      // find distance between debris i and the two walls
      ld distToTop = width;
      ld distToBottom = width;
      for (int it = 0; it < numV[i]; it++) {
        distToTop = min(distToTop, abs(top_y - p[i][it].imag()));
        distToBottom = min(distToBottom, abs(bottom_y - p[i][it].imag()));
      }
      dist[i][TOP] = dist[TOP][i] = distToTop;
      dist[i][BOTTOM] = dist[BOTTOM][i] = distToBottom;
    }

    // now we find the largest aforementioned edge
    // by running a variant of Floyd Warshall with max instead of +
    for (int k = 0; k < n + 2; k++) {
      for (int i = 0; i < n + 2; i++) {
        for (int j = 0; j < n + 2; j++) {
          dist[i][j] = min(dist[i][j], max(dist[i][k], dist[k][j]));
        }
      }
    }

    ld ans = min(maxRadius, dist[TOP][BOTTOM] / 2);
    if (ans < EPS) {
      cout << "Impossible" << nl;
    } else {
      cout << ans << nl;
    }

  }

  return 0;
}
