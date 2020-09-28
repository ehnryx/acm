//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

//#define FILENAME sadcactus

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;
typedef long double ld;
typedef complex<ld> pt;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 998244353;
const ld EPS = 1e-9;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const ld PI = acos((ld)-1);

void exit_bad() {
  cout << "impossible" << nl;
  exit(0);
}

ld cp(const pt& a, const pt& b) { return imag(conj(a) * b); }
ld dp(const pt& a, const pt& b) { return real(conj(a) * b); }

// Intersection of non-parallel lines a -> b, c -> d.
pt line_inter(const pt &a, const pt &b, const pt &c, const pt &d) {
  return a + cp(c - a, d - c) / cp(b - a, d - c) * (b - a); }

// Projection of (a -> p) to vector (a -> b), SIGNED - positive in front
ld proj_dist(const pt &a, const pt &b, const pt &p) {
  return dp(b - a, p - a) / abs(b - a); }

// SIGNED distance. Pt on the right of vector (a -> b) will be NEGATIVE.
ld lp_dist(const pt &a, const pt &b, const pt &p) {
  return cp(b - a, p - a) / abs(b - a); }

// Line segment (a, b) to pt p distance.
ld lsp_dist(const pt &a, const pt &b, const pt &p) {
  return dp(b - a, p - a) > 0 && dp(a - b, p - b) > 0 ?
    abs(cp(b - a, p - a) / abs(b - a)) : min(abs(a - p), abs(b - p)); }

// Closest pt on line segment (a, b) to pt p.
pt lsp_closest(const pt &a, const pt &b, const pt &p) {
  if (dp(b - a, p - a) > 0 && dp(a - b, p - b) > 0)
    return abs(cp(b-a,p-a))<EPS ? p : line_inter(a,b,p,p+(a-b)*pt(0,1));
  return abs(a - p) < abs(b - p) ? a : b; }

bool on_segment(const pt& a, const pt& b, const pt& p) {
  return dp(p-a, b-a) > 0 && dp(p-b, a-b) > 0;
}

ld angle(const pt& v) {
  return arg(v) * 180 / PI;
}

// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  cout << fixed << setprecision(2);
#if defined(ONLINE_JUDGE) && defined(FILENAME)
  freopen(FILENAME ".in", "r", stdin);
  freopen(FILENAME ".out", "w", stdout);
#endif

  int W, L;
  cin >> W >> L;

  ld r, x1, y1, x2, y2, x3, y3, h;
  cin >> r >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> h;

  pt v1(x1, y1), v2(x2, y2), v3(x3, y3);
  pt left(0, L), right(W, L);
  pt lbase(r, h), rbase(W, h);
  pt lseg(r - EPS, h), rseg(W-r + EPS, h);

  pt dir3 = (right - v3) / abs(right - v3);
  pt dir2 = (left - v2) / abs(left - v2);
  pt t1 = v3 - 2*r * dir3;
  pt t0 = v2 - 2*r * dir2;

  if(abs(t1 - v1) > EPS) {
    pt dir1 = (t1 - v1) / abs(t1 - v1);
    if(dp(dir1, dir3) <= 0) {
      exit_bad();
    }

    pt s0 = v1 - 2*r * dir1;
    if(abs(t0 - s0) > EPS) {
      pt dir0 = (t0 - s0) / abs(t0 - s0);

      if(dp(dir1, dir0) >= 0) {
        exit_bad();
      }
      if(dp(dir0, dir2) <= 0) {
        exit_bad();
      }

      pt perp = dir1 * pt(0, 1);
      pt mid = line_inter(v1, t1, t0, t0 + perp);
      pt from = (ld)2*mid - t0;
      pt init = line_inter(from, s0, lbase, rbase);

      if(!on_segment(lseg, rseg, init)) {
        exit_bad();
      }

      if(lsp_dist(init, s0, v2) < 2*r || lsp_dist(init, s0, v3) < 2*r) {
        exit_bad();
      }

      pt launch = (s0 - init) / abs(s0 - init);
      if(dp(launch, dir1) <= 0) {
        exit_bad();
      }

      cout << init.real() << " " << angle(launch) << nl;
    }
  }

  return 0;
}
