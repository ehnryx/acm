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
//const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

ld cp(const pt& a, const pt& b) { return imag(conj(a)*b); }
ld dp(const pt& a, const pt& b) { return real(conj(a)*b); }
inline bool cmp_lex_i(const pt& a, const pt& b) {
  return a.imag()<b.imag()||(a.imag()==b.imag()&&a.real()<b.real());}
pol chull(pol p) {
  sort(p.begin(), p.end(), cmp_lex_i); int top=0, bot=1; pol ch(2*p.size());
  for (int i=0, d=1; i < p.size() && i >= 0; i += d) {
  // If there are no duplicates, can change <= 0 to < 0 to keep redundant points
    while (top > bot && cp(ch[top-1]-ch[top-2], p[i]-ch[top-2]) <= 0) top--;
    ch[top++] = p[i]; if (i == p.size()-1) d = -1, bot = top;
  } ch.resize(max(1, top-1)); return ch;
} // pts returned in ccw order.

ld value(const ld& t, const pt& a, const pt& b) {
	pt c = t*a + (1-t)*b;
	return c.real()*c.imag();
}

ld solve(const pt& a, const pt& b) {
	ld left = 0;
	ld right = 1;
	for (int i=0; i<200; i++) {
		ld first = (2*left+right)/3;
		ld second = (left+2*right)/3;
		if (value(first,a,b) > value(second,a,b)) {
			right = second;
		} else {
			left = first;
		}
	}
	return value((left+right)/2, a, b);
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

	int n, m;
	cin >> n >> m;

	int c; ld a, b;
	vector<pt> p;
	for (int i=0; i<n; i++) {
		cin >> c >> a >> b;
		p.push_back(pt(m*a/c,m*b/c));
	}
	p = chull(p);

	n = p.size();
	ld ans = 0;
	for (int i=n-1,j=0; j<n; i=j++) {
		ans = max(ans, solve(p[i],p[j]));
	}
	cout << ans << nl;

	return 0;
}
