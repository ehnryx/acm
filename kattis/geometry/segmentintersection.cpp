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

namespace ubc {
ld cp(const pt& a, const pt& b) { return imag(conj(a)*b); }
int sgn(const ld& x) { return abs(x) < EPS ? 0 : x < 0 ? -1 : 1; }
bool cmp_lex(const pt& a, const pt& b) {
  return a.real()<b.real()-EPS
    ||  (a.real()<=b.real()+EPS && a.imag()<b.imag()-EPS); }
bool seg_x_seg(pt a, pt b, pt c, pt d) {
  //if(eq(a, b) || eq(c, d)) return 0; // exclude endpoints
  ld sa=abs(b-a), sc=abs(d-c); sa=sa>EPS?1/sa:0; sc=sc>EPS?1/sc:0;
  int r1 = sgn(cp(b-a, c-a) * sa), r2 = sgn(cp(b-a, d-a) * sa);
  int r3 = sgn(cp(d-c, a-c) * sc), r4 = sgn(cp(d-c, b-c) * sc);
  if(!r1 && !r2 && !r3) { // collinear
    if(cmp_lex(b, a)) swap(a, b);
    if(cmp_lex(d, c)) swap(c, d);
    //return cmp_lex(a, d) && cmp_lex(c, b); // exclude endpoints
    return !cmp_lex(d, a) && !cmp_lex(b, c);
  } return r1*r2 <= 0 && r3*r4 <= 0; }//change to < to exclude endpoints
pt line_inter(const pt &a, const pt &b, const pt &c, const pt &d) {
  return a + cp(c - a, d - c) / cp(b - a, d - c) * (b - a); }
}

namespace std {
bool operator<(const pt& a, const pt& b) {
  return a.real() < b.real() or (a.real() == b.real() and a.imag() < b.imag());
}
}

//#define MULTI_TEST
void solve_main([[maybe_unused]] int testnum, [[maybe_unused]] auto& cin) {
  int n;
  cin >> n;
  for(int i=0; i<n; i++) {
    int a, b, x, y;
    cin >> a >> b >> x>> y;
    pt A(a, b), B(x, y);
    cin >> a >> b >> x>> y;
    pt C(a, b), D(x, y);
    if(not ubc::seg_x_seg(A, B, C, D)) {
      cout << "none" << nl;
    } else if(ubc::cp(A - B, C - D) != 0) {
      auto it = ubc::line_inter(A, B, C, D);
      cout << it.real() << " " << it.imag() << nl;
    } else {
      if(B < A) swap(A, B);
      if(D < C) swap(C, D);
      A = max(A, C);
      B = min(B, D);
      if(abs(A - B) < EPS) {
        cout << A.real() << " " << A.imag() << nl;
      } else {
        cout << A.real() << " " << A.imag() << " " << B.real() << " " << B.imag() << nl;
      }
    }
  }
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(2);
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
