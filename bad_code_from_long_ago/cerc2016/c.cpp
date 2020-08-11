#include <bits/stdc++.h>
using namespace std;
//#define _USE_MATH_DEFINES
const long double PI = 3.1415926535897932384626L;

//#define DEBUG

#define ll long long
#define pii pair<int,int>
#define pdd pair<ldouble,ldouble>
#define ldouble long double
#define pt complex<ldouble>
#define ld ldouble
#define nl '\n'
const ll MOD = 1e9+7;
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ldouble EPS = 1e-13;
#define pol vector<pt>

ld cp(const pt& a, const pt& b) { return imag(conj(a)*b); }
inline bool cmp_lex(const pt& a, const pt& b) {
  return a.real()<b.real()-EPS||(a.real()<b.real()+EPS&&a.imag()<b.imag()-EPS);}
inline bool cmp_lex_i(const pt& a, const pt& b) {
  return a.imag()<b.imag()-EPS||(a.imag()<b.imag()+EPS&&a.real()<b.real()-EPS);}
////////////////////////////////////////////////////////////////////////////////
// Graham's scan (UNTESTED)
////////////////////////////////////////////////////////////////////////////////  
pt base; bool cmp_base(const pt& a, const pt& b){
  ld dist = cp(a-base, b-base);
  if (max(abs(a-base), abs(b-base)) > EPS) dist /= max(abs(a-base), abs(b-base));
  if (abs(dist)>EPS) return dist>0; return abs(a-base) < abs(b-base); }
void prep_graham(pol& p) { // assumes p is not empty
  sort(p.begin(), p.end(), cmp_lex); p.push_back(base = p[0]);
  sort(p.begin()+1, p.end()-1, cmp_base); }
// If there are duplicates, can change <= 0 to < 0 to keep redundant points
pol graham(pol p) { pol hull; prep_graham(p);
  for (int i = 0; i < p.size()-1; ) { hull.push_back(p[i++]);
    while (hull.size() > 1 && cp(hull.back() - hull[hull.size()-2],
        p[i] - hull.back()) <= 0) hull.pop_back();
  } return hull; } // pts returned in ccw order.

////////////////////////////////////////////////////////////////////////////////
// 2D convex hull (TESTED SPOJ BSHEEP, UVA 11096)
////////////////////////////////////////////////////////////////////////////////
// Assumes nondegenerate, i.e. CH is not a line. 
pol chull(pol p) {
  sort(p.begin(), p.end(), cmp_lex_i); int top=0, bot=1; pol ch(2*p.size());
  for (int i=0, d=1; i < p.size() && i >= 0; i += d) {
  // If there are no duplicates, can change <= 0 to < 0 to keep redundant points
    while (top > bot && cp(ch[top-1]-ch[top-2], p[i]-ch[top-2]) <= 0) top--;
    ch[top++] = p[i]; if (i == p.size()-1) d = -1, bot = top;
  } ch.resize(max(1, top-1)); return ch; } // pts returned in ccw order.

int main() {
	ios::sync_with_stdio(0); 
	cin.tie(0); cout.tie(0);

	int circ = 5000;

	string s;
	int n;
	cin >> n;
	cin >> s;
	vector<pt> points;
	for (int i = 0; i < n; i++) {
		if (s[i] == 'T') {
			if (i == 0 || s[i-1] == 'C')
				points.push_back(pt(i, 0));
			points.push_back(pt(i+1, 0));
			points.push_back(pt((2*i+1)/2.0, sqrt(3)/2.0));
		}
		else if (s[i] == 'S') {
			if (i == 0 || s[i-1] == 'C')
				points.push_back(pt(i, 0));
			points.push_back(pt(i+1, 0));
			if (i == 0 || s[i-1] != 'S')
				points.push_back(pt(i, 1));
			points.push_back(pt(i+1, 1));
		}
		else {
			for (int j = 0; j < circ; j++) {
				points.push_back(pt((2*i+1)/2.0, 0.5) + 0.5L*exp(pt(0, 2*PI*j/circ)));
			}
		}
	}
	vector<pt> hull = graham(points);
	//vector<pt> hull = chull(points);
	ld ans = abs(hull[0] - hull.back());
	for (int i = 1; i < hull.size(); i++) {
		ans += abs(hull[i] - hull[i-1]);
	}
	cout << fixed << setprecision(10) << ans << nl;

	return 0;
}
