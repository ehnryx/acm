#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
//%:include "utility/output.h"

using ll = long long;
using ld = double;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

using pt = complex<ld>;

namespace ubc {
using pol = vector<pt>;

ld cp(const pt& a, const pt& b) { return imag(conj(a)*b); }
ld dp(const pt& a, const pt& b) { return real(conj(a)*b); }
// dist(const pt& a, const pt& b) ==> abs(a-b)
bool eq(const pt &a, const pt &b) { return abs(a-b) < EPS; }
int sgn(const ld& x) { return abs(x) < EPS ? 0 : x < 0 ? -1 : 1; }
bool cmp_lex(const pt& a, const pt& b) {
  return a.real()<b.real()-EPS
    ||  (a.real()<=b.real()+EPS && a.imag()<b.imag()-EPS); }
inline bool cmp_lex_i(const pt& a, const pt& b) {
  return a.imag()<b.imag()-EPS
    ||  (a.imag()<=b.imag()+EPS && a.real()<b.real()-EPS); }

// Does NOT include points on the ends of the segment.
inline bool on_segment(const pt &a, const pt &b, const pt &p) {
  return abs(cp(b-a, p-a)) / abs(a-b) < EPS &&
    dp(b-a, p-a)>0 && dp(a-b, p-b)>0; }

// Checks if p lies on the boundary of a polygon v.
inline bool on_boundary(const pol &v, const pt &p) {
  bool res = 0; for(int i=v.size()-1, j=0; j<v.size(); i=j++) {
    res |= on_segment(v[i], v[j], p) || abs(p-v[i]) < EPS; }
  return res; }

// orientation does not matter !!!
bool pt_in_polygon(const pt &p, const pol &v, bool strict=false) {
  if (on_boundary(v,p)) return !strict;
  ld res = 0; for(int i = v.size() - 1, j = 0; j < v.size(); i = j++) {
    res += atan2(cp(v[i] - p, v[j] - p), dp(v[i] - p, v[j] - p)); }
  return abs(res) > 1; } // will be either 2*PI or 0
}

//#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  int n, m;
  cin >> n >> m;
  vector<vector<pt>> ps;
  for(int i=0; i<n; i++) {
    int k;
    cin >> k;
    vector<pt> p;
    for(int j=0; j<k; j++) {
      int x, y;
      cin >> x >> y;
      p.emplace_back(x, y);
    }
    ps.push_back(move(p));
  }
  vector<tuple<int, int, int, int, int, int>> traps;
  for(int i=0; i<m; i++) {
    int xs, ys, zs, xt, yt, zt;
    cin >> xs >> ys >> zs >> xt >> yt >> zt;
    traps.emplace_back(xs, ys, zs, xt, yt, zt);
  }

  ld l = 0;
  ld r = atan(1e7);
  for(int bs=0; bs<50; bs++) {
    ld q = (l + r) / 2;
    ld tq = tan(q);

    bool ok = true;
    for(int i=0; i<n && ok; i++) {
      bool found = false;
      for(auto [xs, ys, zs, xt, yt, zt] : traps) {
        pt s(xs, ys), t(xt, yt);
        ld hs = zs * tq, ht = zt * tq;
        pt dir = (t - s) / abs(t - s) * pt(0, 1);
        vector<pt> cur = {
          s + dir * hs,
          s - dir * hs,
          t - dir * ht,
          t + dir * ht,
        };

        bool good = true;
        for(auto v : ps[i]) {
          good &= ubc::pt_in_polygon(v, cur);
        }
        if(found |= good) {
          break;
        }
      }

      ok &= found;
    }

    if(ok) {
      r = q;
    } else {
      l = q;
    }
  }

  if(r == atan(1e7)) {
    cout << "impossible" << nl;
  } else {
    cout << r * 180 / acos((ld)-1) << nl;
  }
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
