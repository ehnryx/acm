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

  // dot product
  ld dp(const pt& a, const pt& b) { return real(conj(a)*b); }

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

  int T;
  cin >> T;
  while (T--) {

    int n;
    cin >> n;

    // get the triangle
    vector<pt> triangle;
    for (int i = 0; i < 3; i++) {
      int x, y;
      cin >> x >> y;
      triangle.push_back(pt(x, y));
    }

    // Remember to check for (edge) cases.
    // Can the triangle be degenerate? Does the orientation matter?

    // for each point, we check whether it lies inside the triangle
    for (int i = 0; i < n; i++) {
      int x, y;
      cin >> x >> y;

      if (CodeArchive::pt_in_polygon(pt(x, y), triangle)) {
        cout << "DANGER" << nl;
      } else {
        cout << "SAFE" << nl;
      }
    }

  }

  return 0;
}
