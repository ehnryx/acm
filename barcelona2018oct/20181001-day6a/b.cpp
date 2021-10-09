#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef complex<ld> pt;

const char nl = '\n';

const ld EPS = 1e-7;
const ld PI = acos((ld)-1);
const ld INF = 1e17;

ld cp(const pt& a, const pt& b) { return imag(conj(a)*b); }
ld dp(const pt& a, const pt& b) { return real(conj(a)*b); }
bool eq(const pt& a, const pt& b) { return abs(a-b)<EPS; }

bool on_segment(const pt& a, const pt& b, const pt& p) {
  return eq(a,p) || eq(b,p) ||
    (abs(cp(b-a,p-a))<EPS && dp(b-a,p-a)>0 && dp(a-b,p-b)>0);
}

pt line_inter(const pt& a, const pt& b, const pt& c, const pt& d) {
  return a + cp(c-a, d-c) / cp(b-a, d-c) * (b-a);
}
ld lp_dist(const pt& a, const pt& b, const pt& p) {
  return cp(b-a, p-a) / abs(b-a);
}

vector<pt> cls_inter(const pt& c, const ld& r, const pt& a, const pt& b) {
  ld d = abs(lp_dist(a, b, c));
  if (d > r) return {};

  pt n = (a-b)*pt(0,1);
  pt m = line_inter(c, c+n, a, b);

  pt u = sqrt(r*r-d*d) / abs(a-b) * (a-b);
  vector<pt> res;
  if (on_segment(a, b, m+u)) res.push_back(m+u);
  if (on_segment(a, b, m-u)) res.push_back(m-u);
  return res;
}

ld cw_ang(const pt& a, const pt& b) {
  ld ang = -arg(b/a);
  if (ang < -EPS) ang += 2*PI;
  return ang;
}

// REAL CODE

struct Point {
  ld ang, dist;
  pt pos;
  Point(ld a, ld d, pt p): ang(a), dist(d), pos(p) {}
  bool operator < (const Point& o) const {
    if (abs(ang-o.ang) < EPS) return dist > o.dist;
    else return ang < o.ang;
  }
};

int n;
vector<pt> p;

pt pivot(const pt& a, const pt& b) {
  pt res;
  ld minv = INF;
  for (int i=0; i<n; i++) {
    int j = (i+1==n?0:i+1);
    if (on_segment(p[i], p[j], a)) return a;
    if (on_segment(a, b, p[i])) {
      ld d = abs(p[i]-a);
      if (d<minv) {
        res = p[i];
        minv = d;
      }
    }
  }
  return res;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout << fixed << setprecision(7);
  //cerr << fixed << setprecision(2);

  ld L, R;
  cin >> L >> R >> n;
  R *= 2*PI;

  ld x, y;
  for (int i=0; i<n; i++) {
    cin >> x >> y;
    p.push_back(pt(x,y));
  }

  pt ans(0,0);
  pt A(0,0);
  pt B(0,L);

  int scnt = 0;
  while (R > 1e-9 && scnt < 7) {
    // find O by iteration
    pt O = pivot(A,B);
    //cerr << "rotate " << A << " " << B << " @ " << O << nl;

    // calculate circles
    ld forw = abs(O-A);
    ld back = abs(O-B);
    //cerr << "  forw: " << forw << "  back: " << back << nl;

    // calculate Points
    Point best(INF,-INF,pt(INF,INF));

    for (int i=0; i<n; i++) {
      int j = (i+1==n?0:i+1);
      int k = (i==0?n-1:i-1);

      // calculate vertices
      if (!eq(p[i],O)) {
        ld dist = abs(p[i]-O);
        if (dist < forw+EPS) {
          ld ang = cw_ang(A-O, p[i]-O);
          if (cp(p[i]-O, p[j]-p[i]) < -EPS) {
            if (cp(p[i]-O, p[i]-p[k]) > -EPS) {
              best = min(best, Point(ang, dist, p[i]));
            }
          }
        }
        if (dist < back+EPS) {
          ld ang = cw_ang(B-O, p[i]-O);
          if (cp(p[i]-O, p[j]-p[i]) < -EPS) {
            if (cp(p[i]-O, p[i]-p[k]) > -EPS) {
              best = min(best, Point(ang, dist, p[i]));
            }
          }
        }
      }

      // calculate intersects
      for (pt it : cls_inter(O, forw, p[i], p[j])) {
        if (cp(p[j]-p[i], (it-O)*pt(0,1)) > EPS) {
          ld ang = cw_ang(A-O, it-O);
          best = min(best, Point(ang, abs(it-O), it));
        }
      }
      for (pt it : cls_inter(O, back, p[i], p[j])) {
        if (cp(p[j]-p[i], (it-O)*pt(0,1)) > EPS) {
          ld ang = cw_ang(B-O, it-O);
          best = min(best, Point(ang, abs(it-O), it));
        }
      }
    }

    //cerr << "  hit @ " << best.pos << " w/ " << best.ang << " d " << best.dist << nl;

    // do the turns
    if (best.ang < EPS) {
      scnt++;
      swap(A,B);
    } else {
      scnt = 0;
      best.ang = min(best.ang, R);
      R -= best.ang;
      pt rot = exp(pt(0,-best.ang));
      A = O + (A-O)*rot;
      B = O + (B-O)*rot;
      ans = O + (ans-O)*rot;
      if (abs(A-best.pos) > abs(A-O)) swap(A,B);
    }
    //cerr << "  answer moved to " << ans << nl;
  }

  cout << ans.real() << " " << ans.imag() << nl;

  return 0;
}
