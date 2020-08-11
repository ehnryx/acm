#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

ld cp(const pt& a, const pt& b) { return imag(conj(a)*b); }
ld dp(const pt& a, const pt& b) { return real(conj(a)*b); }
// dist(const pt& a, const pt& b) ==> abs(a-b)
inline bool eq(const pt &a, const pt &b) { return abs(a-b) < EPS; }
inline ld sgn(const ld& x) { return abs(x) < EPS ? 0 : x/abs(x); }
inline bool cmp_lex(const pt& a, const pt& b) {
  return a.real()<b.real()-EPS||(a.real()<b.real()+EPS&&a.imag()<b.imag()-EPS);}
inline bool cmp_lex_i(const pt& a, const pt& b) {
  return a.imag()<b.imag()-EPS||(a.imag()<b.imag()+EPS&&a.real()<b.real()-EPS);}
// handles ALL cases, uncomment/edit the 3 marked lines to exclude endpoints
bool seg_x_seg(pt a1, pt a2, pt b1, pt b2) {
  //if (eq(a1,a2) || eq(b1,b2)) return false; // uncomment to exclude endpoints
  ld za = abs(a2-a1), zb = abs(b2-b1); za=za>EPS?1/za:0; zb=zb>EPS?1/zb:0;
  int s1 = sgn(cp(a2-a1, b1-a1)*za), s2 = sgn(cp(a2-a1, b2-a1)*za);
  int s3 = sgn(cp(b2-b1, a1-b1)*zb), s4 = sgn(cp(b2-b1, a2-b1)*zb);
  if(!s1 && !s2 && !s3) { // collinear
    if (cmp_lex(a2, a1)) swap(a1, a2); if (cmp_lex(b2, b1)) swap(b1, b2);
    //return cmp_lex(a1, b2) && cmp_lex(b1, a2);//uncomment to exclude endpoints
    return !cmp_lex(b2, a1) && !cmp_lex(a2, b1);
  } return s1*s2 <= 0 && s3*s4 <= 0; } //change to < to exclude endpoints
 
inline pt line_inter(const pt &a, const pt &b, const pt &c, const pt &d) {
  return a + cp(c - a, d - c) / cp(b - a, d - c) * (b - a); }
 
// Projection of (a -> p) to vector (a -> b), SIGNED - positive in front
inline ld proj_dist(const pt &a, const pt &b, const pt &p) {
  return dp(b - a, p - a) / abs(b - a); }
 
// SIGNED distance. Pt on the right of vector (a -> b) will be NEGATIVE.
inline ld lp_dist(const pt &a, const pt &b, const pt &p) {
  return cp(b - a, p - a) / abs(b - a); }
 
// Line segment (a, b) to pt p distance.
inline ld lsp_dist(const pt &a, const pt &b, const pt &p) {
  return dp(b - a, p - a) > 0 && dp(a - b, p - b) > 0 ?
    abs(cp(b - a, p - a) / abs(b - a)) : min(abs(a - p), abs(b - p));
}

//#define FILEIO
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(2);
#ifdef FILEIO
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#endif

	int n;
	cin >> n;
	for (int i=0; i<n; i++) {
		int a,b,c,d,e,f,g,h;
		cin >> a >> b >> c >> d >> e >> f >> g >> h;
		if (seg_x_seg(pt(a,b),pt(c,d),pt(e,f),pt(g,h))) {
			cout << "0.00" << nl;
		} else {
			cout << min(
				min(lsp_dist(pt(a,b),pt(c,d),pt(e,f)), lsp_dist(pt(a,b),pt(c,d),pt(g,h))),
				min(lsp_dist(pt(e,f),pt(g,h),pt(a,b)), lsp_dist(pt(e,f),pt(g,h),pt(c,d)))
			) << nl;
		}
	}

	return 0;
}
