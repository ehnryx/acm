#include <bits/stdc++.h>
using namespace std;

//%:include "utility/defines.h"
//%:include "utility/fast_input.h"
//%:include "utility/output.h"

using ll = long long;
using ld = long double;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

struct pt {
  int x, y;
  pt(int _x, int _y): x(_x), y(_y) {}
  pt operator - (const pt& o) const { return pt(x-o.x, y-o.y); }
  pt operator + (const pt& o) const { return pt(x+o.x, y+o.y); }
};

ll cross(pt a, pt b) {
  return (ll)a.y*b.x - (ll)a.x*b.y;
}

struct ray {
  int x, y, s, add;
  ray(int _x, int _y, int _s, int a): x(_x), y(_y), s(_s), add(a) {}
  bool operator < (const ray& o) const {
    if(s != o.s) return s < o.s;
    //  (x/y) < (o.x/o.y)
    if(x*o.y != y*o.x) return x*o.y < y*o.x;
    return add > o.add; // add first
  }
  bool operator > (const ray& o) const {
    return o < *this;
  }
};

namespace ubc {
  using P = complex<double>;
  using pol = vector<P>;

  double cp(const P& a, const P& b) { return imag(conj(a) * b); }
  int sgn(double x) { return x < -EPS ? -1 : x > EPS ? 1 : 0; }
  P line_inter(const P& a, const P& b, const P& c, const P& d) {
    return a + cp(c-a, d-c) / cp(b-a, d-c) * (b-a);
  }

  pol cut_polygon(const pol& v, const P& a, const P& b) {
    if(v.empty()) return {};
    pol out;
    for(int i=v.size()-1, j=0; j<v.size(); i=j++) {
      if(cp(b-a, v[i]-a) < EPS) out.push_back(v[i]);
      if(sgn(cp(b-a, v[i]-a)) * sgn(cp(b-a, v[j]-a)) < 0) {
        P p = line_inter(a, b, v[i], v[j]);
        if(!out.size() || abs(out.back()-p) > EPS) out.push_back(p);
      }
    }
    while(out.size() && abs(out[0]-out.back()) < EPS) out.pop_back();
    return out;
  }

  double area(const pol& v) {
    if(v.empty()) return 0;
    double res = 0;
    for(int i=v.size()-1, j=0; j<v.size(); i=j++) {
      res += cp(v[i], v[j]);
    }
    return abs(res)/2;
  }
}

ld get_area(pt v, pt u, int s, int len) {
  if(s == 0) {
    v.x = -v.x;
    v.y = -v.y;
  }
  v = v + u;
  // u->v (keep area left of)
  vector<ubc::P> bs = {
    ubc::P(0, 0), ubc::P(len, 0), ubc::P(len, len), ubc::P(0, len),
  };
  return ubc::area(ubc::cut_polygon(bs, ubc::P(v.x, v.y), ubc::P(u.x, u.y))) / (len*len);
}

ld calc_area(ld angle, ubc::P at, int len) {
  vector<ubc::P> bs = {
    ubc::P(0, 0), ubc::P(len, 0), ubc::P(len, len), ubc::P(0, len),
  };
  ubc::P dir = exp(ubc::P(0, angle));
  return ubc::area(ubc::cut_polygon(bs, at, at + dir));
}

ld solve_one(int len, const vector<pt>& v, int base) {
  using namespace ubc;
  int n = size(v);
  ld ans = 0;

  vector<pt> alldirs = {
    pt(0, 1), pt(1, 0), pt(1, 1), pt(1, -1),
    pt(0, -1), pt(-1, 0), pt(-1, -1), pt(-1, 1),
  };
  for(pt dir : alldirs) {
    int cnt = 0;
    for(int i=0; i<n; i++) {
      cnt += (cross(dir, v[i] - v[base]) >= 0);
    }
    assert(cnt <= n);
    ans = max(ans, (ld)cnt / n - get_area(dir, v[base], 0, len));
  }

  ld step = M_PIl / 4;
  P at(v[base].x, v[base].y);
  for(int s=0; s<8; s++) {
    ld l = s * step;
    ld r = (s+1) * step;
    for(int bs=0; bs<99; bs++) {
      ld lm = (5*l + 4*r) / 9;
      ld rm = (4*l + 5*r) / 9;
      ld larea = calc_area(lm, at, len);
      ld rarea = calc_area(rm, at, len);
      if(larea < rarea) {
        r = rm;
      } else {
        l = lm;
      }
    }
    P dir = exp(P(0, r));
    int cnt = 0;
    for(int i=0; i<n; i++) {
      cnt += (cp(dir, P(v[i].x, v[i].y) - at) <= EPS);
    }
    ans = max(ans, (ld)cnt / n - calc_area(r, at, len) / (len*len));
  }

  return ans;
}

ld solve(int len, const vector<pt>& v, int base) {
  ld ans = solve_one(len, v, base);

  //cerr << "RUN " << base << " -> " << v[base].x << " " << v[base].y << nl;
  int n = size(v);
  vector<ray> rot;
  int cnt = 1;
  for(int i=0; i<n; i++) {
    if(i == base) continue;
    pt dir = v[i] - v[base];
    cnt += (dir.y > 0 || (dir.y == 0 && dir.x > 0));
    int add = 1;
    if(dir.y < 0 || (dir.y == 0 && dir.x < 0)) {
      dir.y = -dir.y;
      dir.x = -dir.x;
      add = -1;
    }
    //cerr << "  " << v[i].x << " " << v[i].y << " -> " << dir.x << " " << dir.y << " with add " << add << nl;
    rot.emplace_back(dir.x, dir.y, 1, -add);
    rot.emplace_back(dir.x, dir.y, 0, add);
  }
  sort(begin(rot), end(rot), greater<>());

  //cerr << "init cnt = " << cnt << nl;

  //ld ans = 0;
  for(auto [x, y, s, a] : rot) {
    assert(cnt <= n);
    if(a < 0) ans = max(ans, (ld)cnt / n - get_area(pt(x, y), v[base], s, len));
    cnt += a;
    //cerr << "AT " << ubc::P(x, y) << " w/ cnt " << cnt << nl;
    if(a > 0) ans = max(ans, (ld)cnt / n - get_area(pt(x, y), v[base], s, len));
    assert(cnt <= n);
  }
  return ans;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#ifdef USING_FAST_INPUT
  fast_input cin;
#endif

  int n, m;
  cin >> n >> m;
  vector<pt> v;
  for(int i=0; i<m; i++) {
    int a, b;
    cin >> a >> b;
    v.emplace_back(a, b);
  }

  ld ans = 0;
  for(int i=0; i<m; i++) {
    ans = max(ans, solve(n, v, i));
  }
  cout << ans << nl;

  return 0;
}
