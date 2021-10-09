#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;

const int INF = 0x3f3f3f3f;

#define nl '\n'

struct Edge {
  pt a, b, c;
  int sign;
};
typedef vector<Edge> pol;

const ld PI = acos((ld)-1);
const ld EPS = 1e-10;

ld cp(const pt& a, const pt& b) { return imag(conj(a)*b); }
int sgn(const ld& x) { return x < -EPS ? -1 : x < EPS ? 0 : 1; }

int cc_inter(pt p1, ld r1, pt p2, ld r2, pt&i1, pt&i2) {
  ld dq=norm(p1-p2), rq=r1*r1-r2*r2; pt c=(p1+p2)*(ld)0.5 + (p2-p1)*rq*(ld)0.5/dq;
  ld dt=(ld)2*dq*(r1*r1+r2*r2)-dq*dq-rq*rq;
  if (dt<-EPS) return 0; 
  if (dt<EPS) { i1=i2=c; return 1; }
  dt=sqrt(dt)*0.5/dq; i1=c+(p2-p1)*pt(0,1)*dt; i2=c-(p2-p1)*pt(0,1)*dt;
  return 2;
}

pol make_circle(pt c, ld r) {
  vector<ld> ang;
  for (int i=0; i<3; i++) {
    ang.push_back(2*PI*i/3);
  }

  pol out;
  for (int i=2,j=0; j<3; i=j++) {
    out.push_back({c+r*exp(pt(0,ang[i])), c+r*exp(pt(0,ang[j])), c, 1});
  }
  return out;
}

ld area(const pol& p) { 
  int n = p.size(); 
  ld s = 0; ld extra = 0;
  for (const Edge& e : p) {
    s += cp(e.a, e.b)/2;
    ld r = abs(e.c-e.a);
    pt a = e.a-e.c;
    pt b = e.b-e.c;
    extra += e.sign * (r*r*abs(arg(a/b))/2 - abs(cp(a,b)/2));
  }
  return abs(s) + extra;
}

vector<pt> intersect(const Edge& e, const pt& c, ld r) {
  pt i1, i2;
  int cnt = cc_inter(e.c, abs(e.a-e.c), c, r, i1, i2);
  if (cnt < 2) return {};
  ld s = arg(e.a-e.c);
  if (s < -EPS) s += 2*PI;
  ld t = arg(e.b-e.c);
  if (t < -EPS) t += 2*PI;
  ld a1 = arg(i1-e.c);
  if (a1 < -EPS) a1 += 2*PI;
  ld a2 = arg(i2-e.c);
  if (a2 < -EPS) a2 += 2*PI;
  if (abs(a2-s) < abs(a1-s)) {
    swap(a1,a2);
    swap(i1,i2);
  }

  vector<pt> out;
  if (abs(abs(a1-s)+abs(a1-t)-abs(s-t)) < EPS) {
    out.push_back(i1);
  }
  if (abs(abs(a2-s)+abs(a2-t)-abs(s-t)) < EPS) {
    out.push_back(i2);
  }
  return out;
}

void circle_intersect_out(vector<pol>& nxt, const pol& p, const pt& c, ld r) {
  int n = p.size();
  int start = -1;
  pt first;
  for (int i=0; i<n; i++) {
    const Edge& e = p[i];
    vector<pt> inter = intersect(e, c, r);
    bool ok = false;
    for (int it : inter) {
      pt ctan = (it-c)*pt(0,1);
      bool dir = (cp(it-e.c, e.a-e.c) < 0);
      pt ptan = (it-e.c)*pt(0,1);
      if (dir) 
      if (cp(ctan, ptan) < 0) {
        ok = true;
        first = it;
        start = i;
        break;
      }
    }
    if (ok) break;
  }
  if (start == -1) {
    // cut?
  }
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int T;
  cin >> T;
  for (int casenum=1; casenum<=T; casenum++) {
    int num;
    cin >> num;

    vector<pol> pos, neg;
    int x, y, a, b;
    cin >> x >> y >> a >> b;

    for (int i=0; i<num; i++) {
      cin >> x >> y >> a >> b;
      pt center(x,y);
      int out = a+b;
      int in = a-b;

      vector<pol> nxtpos, nxtneg;
      for (const pol& p : nxtpos) {
        circle_intersect(nxtpos, p, center, out);
        circle_intersect(nxtpos, p, center, in);
      }
      for (const pol& p : nxtneg) {
        circle_intersect(nxtneg, p, center, out);
        circle_intersect(nxtneg, p, center, in);
      }
      pos = nxtpos;
      neg = nxtneg;
      pos.push_back(make_circle(pt(x,y), out));
      if (in > 0) neg.push_back(make_circle(pt(x,y), in));
    }

    ld ans = 0;
    for (const pol& it : pos) {
      ans += area(it);
    }
    for (const pol& it : neg) {
      ans -= area(it);
    }
    cout << "Case " << casenum << ": " << ans << nl;
  }

  return 0;
}
