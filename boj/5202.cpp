#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
//%:include "utility/output.h"

using ll = long long;
using ld = long double;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

using pt = complex<ld>;

constexpr auto PI = numbers::pi_v<ld>;

namespace ubc {
using pol = vector<pt>;
ld cp(const pt& a, const pt& b) { return imag(conj(a)*b); }
int sgn(const ld& x) { return abs(x) < EPS ? 0 : x < 0 ? -1 : 1; }
pt line_inter(const pt &a, const pt &b, const pt &c, const pt &d) {
  return a + cp(c - a, d - c) / cp(b - a, d - c) * (b - a); }
pol cut_polygon(const pol &v, const pt &a, const pt &b) { pol out;
  for(int i = v.size() - 1, j = 0; j < v.size(); i = j++) {
    if(cp(b-a, v[i]-a) < EPS) out.push_back(v[i]);
    if(sgn(cp(b-a, v[i]-a)) * sgn(cp(b-a, v[j]-a)) < 0) {
      pt p = line_inter(a, b, v[i], v[j]);
      if(!out.size() || abs(out.back() - p) > EPS) out.push_back(p); } }
  while(out.size() && abs(out[0] - out.back()) < EPS) out.pop_back();
  return out; }
ld area(const pol &v) { ld s = 0; int n = v.size();
  for(int i = n-1, j = 0; j < n; i = j++) s += cp(v[i], v[j]);
  return abs(s)/2;}
}

const int S = 4e4;

#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  cout << "Data Set " << testnum << ":" << nl;
  ld w, h, r, d, a1, a2;
  cin >> w >> h >> r >> d >> a1 >> a2;
  a1 = a1 * PI / 180;
  a2 = a2 * PI / 180;
  ld x1 = d * tan(PI/2 - a1);
  ld x2 = d * tan(PI/2 - a2);
  pt c1 = min(x1, x2);
  pt c2 = max(x1, x2);

  vector<pt> p;
  for(int i=0; i<S; i++) {
    auto v = c1 + r * exp(pt(0, PI + 2*PI * i/S));
    if(abs(v - c2) < r) {
      p.push_back(v);
    }
  }
  for(int i=0; i<S; i++) {
    auto v = c2 + r * exp(pt(0, 2*PI * i/S));
    if(abs(v - c1) < r) {
      p.push_back(v);
    }
  }

  for(auto [u, v] : {
      pair(pt(-h/2, -w/2), pt(-h/2,  w/2)),
      pair(pt(-h/2,  w/2), pt( h/2,  w/2)),
      pair(pt( h/2,  w/2), pt( h/2, -w/2)),
      pair(pt( h/2, -w/2), pt(-h/2, -w/2)), }) {
    p = ubc::cut_polygon(p, u, v);
  }

  ld good = ubc::area(p);
  ld ans = 100 * (1 - good / (w * h));
  cout << fixed << setprecision(2) << ans << "%" << nl;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);
#ifdef USING_FAST_INPUT
  fast_input cin;
#endif

  int T = 1;
#ifdef MULTI_TEST
  cin >> T;
#endif
  for(int testnum=1; testnum<=T; testnum++) {
    solve_main(testnum, cin);
  }

  return 0;
}
