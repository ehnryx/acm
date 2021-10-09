#include <bits/stdc++.h>
using namespace std;

#define ld long double
#define pt complex<ld>
#define nl '\n'

const ld EPS = 1e-9;

inline ld cp(const pt& a, const pt& b) { 
  return imag(conj(a)*b); 
}
inline pt line_inter(const pt& a, const pt& b, const pt& c, const pt& d) {
  return a + cp(c-a, d-c) / cp(b-a, d-c) * (b-a); 
}
inline ld lp_dist(const pt& a, const pt& b, const pt& p) {
  return cp(b-a, p-a) / abs(b-a);
}

pt pfirst;
struct Point {
  pt p;
  int pos;
  Point(const pt& p, int s):
    p(p), pos(s) {}
  bool operator < (const Point& other) const {
    return abs(pfirst-p) < abs(pfirst-other.p);
  }
};

ld find_length(const pt& first, const pt& second, const vector<pt>& p) {
  pfirst = 1e7L*(first-second) + first;

  vector<Point> inters;
  int n = p.size();
  for (int i = 0; i < n; i++) {
    if (abs(lp_dist(pfirst, second, p[i])) < EPS) {
      if (abs(lp_dist(pfirst, second, p[(i+n-1)%n])) < EPS
          && abs(lp_dist(pfirst, second, p[(i+1)%n])) < EPS) {
        continue;
      } else if (abs(lp_dist(pfirst, second, p[(i+n-1)%n])) < EPS) {
        inters.push_back(Point(p[i], cp(pfirst-p[i], p[(i+1)%n]-p[i]) > 0));
      } else if (abs(lp_dist(pfirst, second, p[(i+1)%n])) < EPS) {
        inters.push_back(Point(p[i], cp(pfirst-p[i], p[(i+n-1)%n]-p[i]) > 0));
      } else if (lp_dist(pfirst, second, p[(i+n-1)%n])*lp_dist(pfirst, second, p[(i+1)%n]) < -EPS) {
        inters.push_back(Point(p[i], -1));
      }
    }
    if (lp_dist(pfirst, second, p[i])*lp_dist(pfirst, second, p[(i+1)%n]) < -EPS) {
      inters.push_back(Point(line_inter(pfirst, second, p[i], p[(i+1)%n]), -1));
    }
  }
  sort(inters.begin(), inters.end());

  ld res = 0;
  pt prev;
  bool in_poly = false;
  bool in_on_pos = false;
  bool parallel = false;
  for (const Point& it : inters) {
    // not parallel
    if (it.pos == -1) {
      if (in_poly) {
        res = max(res, abs(prev - it.p));
        in_poly = false;
      } else {
        prev = it.p;
        in_poly = true;
      }
    }
    // parallel
    else if (parallel) {
      parallel = false;
      if (in_on_pos == it.pos) {
        res = max(res, abs(prev - it.p));
        in_poly = false;
      }
    }
    else {
      parallel = true;
      if (in_poly) {
        in_on_pos = !it.pos;
      } else {
        in_on_pos = it.pos;
        prev = it.p;
        in_poly = true;
      }
    }
  }

  return res;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(9);

  ld x, y;
  vector<pt> points;

  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> x >> y;
    points.push_back(pt(x,y));
  }

  ld ans = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < i; j++) {
      ans = max(ans, find_length(points[i], points[j], points));
    }
  }
  
  cout << ans << nl;

  return 0;
}
