#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ld EPS = 1e-13L;
const ld PI = acos((ld)-1);
/*
struct cplx {
  ld x,y; cplx() { x=y=0; }
  cplx(ld nx, ld ny=0) { x=nx; y=ny; }
  cplx operator + (const cplx& c) const { return {x+c.x, y+c.y}; }
  cplx operator - (const cplx& c) const { return {x-c.x, y-c.y}; }
  cplx operator * (const cplx& c) const { return {x*c.x - y*c.y, x*c.y + y*c.x}; }
  cplx operator * (const ld& c) const { return {x*c,y*c}; }
  cplx operator / (const ld& c) const { return {x/c,y/c}; }
};
typedef cplx pt;
ld cp(const pt& a, const pt& b) { return a.x*b.y - b.x*a.y; }
ld norm(const pt& a) { return a.x*a.x + a.y*a.y; }
ld abs(const pt& a) { return sqrt(norm(a)); }
ld arg(const pt& a) { return atan2(a.y, a.x); }
*/

typedef complex<ld> pt;
ld cp(const pt& a, const pt& b) { return imag(conj(a)*b); }

int cc_inter(pt p1, ld r1, pt p2, ld r2, pt& i1, pt& i2) {
  if (abs(p1-p2)<0.5) return 0;
  ld dq=norm(p1-p2), rq=r1*r1-r2*r2; pt c=(p1+p2)*(ld)0.5 + (p2-p1)*rq*(ld)0.5/dq;
  ld dt=(ld)2*dq*(r1*r1+r2*r2)-dq*dq-rq*rq;
  if (dt<0) { return 0; }
  dt=sqrt(dt)*(ld)0.5/dq; i1=c+(p2-p1)*pt(0,1)*dt; i2=c-(p2-p1)*pt(0,1)*dt;
  return 2;
}

ld chord(ld s, ld t, ld r) {
  return r * sqrt(2*(1-cos(s-t)));
}

bool contains(ld x, pair<ld,ld> it) {
  while (it.second < it.first) it.second += 2*PI;
  while (x < it.first) x += 2*PI;
  return x <= it.second;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout << fixed << setprecision(15);

  pt o(0,0);

  int T;
  cin >> T;
  for (int testnum=1; testnum<=T; testnum++) {
    int n, r;
    cin >> n >> r;

    vector<ld> segs;
    vector<pair<ld,ld>> range;
    for (int i=0; i<n; i++) {
      int x, y, ri;
      cin >> x >> y >> ri;
      pt c(x,y);
      pt i1, i2;
      if (cc_inter(o, r, c, ri, i1, i2) == 2) {
        if (cp(c, i1) > 0) swap(i1, i2);
        ld s = arg(i1);
        ld t = arg(i2);
        // points
        segs.push_back(s);
        segs.push_back(t);
        // range
        range.push_back({s,t});
      }
    }

    ld ans = (segs.empty() ? 2*r : 0);
    // points
    for (int i=0; i<segs.size(); i++) {
      for (int j=0; j<i; j++) {
        ans = max(ans, chord(segs[i], segs[j], r));
      }
    }
    // ranges
    for (const ld& p : segs) {
      bool good = true;
      for (const pair<ld,ld>& it : range) {
        if (contains(p-3*PI, it)) {
          good = false;
          break;
        }
      }
      if (good) {
        ans = 2*r;
        break;
      }
    }

    cout << "Case #" << testnum << ": " << ans << nl;
  }

  return 0;
}
