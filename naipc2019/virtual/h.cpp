#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#define nl '\n'
typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;

const int INF = 0x3f3f3f3f;
const ld PI = M_PIl;
const ld EPS = 1e-9;

pair<pt, pt> circle_tangent(ld r1, ld r2, ld d, int k) { // use the fcn below
  ld dr = (k & 2) ? (-r1-r2) : (r2-r1); ld t = asin(dr / d);
  pt p1=polar(r1, PI/2+t), p2=polar(r2, PI/2+t); if(k&2) p2*=-1; p2+=pt(d,0);
  if(k&1){ p1=pt(p1.real(),-p1.imag()); p2=pt(p2.real(),-p2.imag()); }
  return make_pair(p1, p2); }
// tested 2008wf conveyor; tangent of 2 circles; CAUTION: INTERSECTION IS BAD
// k=0 top-top, k=1 bot-bot, k=2 top-bot, k=3 bot-top. Also works for points.
pair<pt, pt> circle_tangent(pt p1, ld r1, pt p2, ld r2, int k) {
  // translate/rotate so c1 at (0,0), c2 at x-axis
  pt d = p2-p1; pair<pt, pt> p = circle_tangent(r1, r2, abs(d), k); d /= abs(d);
  p.first *= d; p.second *= d; p.first += p1; p.second += p1; return p;
}

ld angle(const pt& x) {
  ld res = arg(x/pt(0,-1));
  if (res < -EPS) res += 2*PI;
  return res;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout << fixed << setprecision(17);

  int x,y;
  cin >> x >> y;
  if (y<0) y = -y;
  pt p(x,y);
  ld dist = abs(p);

  ld v,w;
  cin >> v >> w;

  ld t = 2*PI/w;
  ld r = v*t/(2*PI);
  //cerr << "radius: " << r << nl;

  auto calc = [&] (ld ang) {
    pt c = r*exp(pt(0,ang));
    pt a, b;
    tie(a,b) = circle_tangent(c, r, p, 0, 1);
    ld res = abs(a-b)/v + angle(a-c)/w;
    //cerr << "CALC " << ang << " -> " << c << " -> " << a << " -- " << b << " -> " << res << nl;
    //cerr << "  -> " << abs(a-b) << " / " << v << " + " << angle(a-c) << " / " << w << nl;
    return res;
  };

  auto search = [&] (const ld& offset) {
    //cerr << "OFFSET: " << offset << nl;
    ld left = (dist>2*r ? PI/2 : max(PI/2,offset+acos(dist/2/r)));
    ld right = offset + PI/2;
    //cerr << "SEARCH " << left << " " << right << nl;
    for (int bs=0; bs<420; bs++) {
      ld first = (2*left+right)/3;
      ld second = (left+2*right)/3;
      if (calc(first) < calc(second)) {
        right = second;
      } else {
        left = first;
      }
    }
    //cerr << "angle: " << left << nl;
    return calc(left);
  };

  cout << search(arg(p)) << nl;

  return 0;
}
