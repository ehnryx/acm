#include <bits/stdc++.h>
using namespace std;

//%:include "utility/fast_input.h"
//%:include "utility/output.h"

%:include "number/fraction.h"

using ll = long long;
//using ld = long double;
using ld = fraction<ll>;
using pt = complex<ld>;

constexpr char nl = '\n';
constexpr int MOD = 998244353;
//constexpr ld EPS = 1e-9L;
random_device _rd; mt19937 rng(_rd());

int sgn(ld f) {
  return f < 0 ? -1 : f > 0 ? 1 : 0;
}

namespace ubc {

using pol = vector<pt>;

ld cp(const pt& a, const pt& b) { return imag(conj(a)*b); }
ld dp(const pt& a, const pt& b) { return real(conj(a)*b); }
// dist(const pt& a, const pt& b) ==> abs(a-b)

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

// cut left of a -> b
pol cut_polygon(const pol &v, const pt &a, const pt &b) { pol out;
  for(int i = v.size() - 1, j = 0; j < v.size(); i = j++) {
    if(cp(b-a, v[i]-a) <= 0) out.push_back(v[i]);
    if(sgn(cp(b-a, v[i]-a)) * sgn(cp(b-a, v[j]-a)) < 0) {
      pt p = line_inter(a, b, v[i], v[j]);
      if(!out.size() || out.back() != p) out.push_back(p); } }
  while(out.size() && out[0] == out.back()) out.pop_back();
  return out; }

ld area(const pol &v) { ld s = 0; int n = v.size();
  for(int i = n-1, j = 0; j < n; i = j++) s += cp(v[i], v[j]);
  return abs(s)/2;}

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
  for(int i=0; i<n; i++) {
    int a, b;
    cin >> a >> b;
    v.emplace_back(2*a + 1, 2*b + 1);
  }

  while(m--) {
    int x, y;
    cin >> x >> y;
    pt A(2*x, 2*y);
    pt B(2*x + 2, 2*y);
    pt C(2*x + 2, 2*y + 2);
    pt D(2*x, 2*y + 2);
    vector<pt> w = v;
    w = ubc::cut_polygon(w, B, A);
    w = ubc::cut_polygon(w, C, B);
    w = ubc::cut_polygon(w, D, C);
    w = ubc::cut_polygon(w, A, D);
    cout << ubc::area(w) / 4 << nl;
  }

  return 0;
}
