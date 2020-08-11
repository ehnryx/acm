#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;
#define nl '\n'

inline void srand() { srand(clock() + time(nullptr)); }

template <class T, class U>
ostream& operator << (ostream& os, const pair<T,U>& v) {
	os << "(" << v.first << "," << v.second << ")"; return os;
}

template <class T>
ostream& operator << (ostream& os, const vector<T>& v) {
	for (const T& it : v) os << it << " "; return os;
}

template <class T>
ostream& operator << (ostream& os, const set<T>& v) {
	os << "{ ";
	for (const T& it : v) os << it << " ";
	os << "}"; return os;
}

template <class T, class U>
ostream& operator << (ostream& os, const map<T,U>& v) {
	os << "{ ";
	for (const pair<T,U>& it : v) os << "{" << it.first << "," << it.second << "} "; 
	os << "}"; return os;
}

template <class T>
inline T sqr(T x) { return x*x; }

const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
//const ld PI = M_PIl;
////////////////////////////////////////////////////////////////////////

const ll MOD = 1e9+7;
const ld EPS = 1e-13;

inline ld cp(const pt& a, const pt& b) { return imag(conj(a)*b); }
inline ld dp(const pt& a, const pt& b) { return real(conj(a)*b); }
inline ld sgn(const ld& x) { return abs(x) < EPS ? 0 : x/abs(x); }
inline ld lp_dist(const pt& a, const pt& b, const pt& p) {
	return cp(b-a, p-a) / abs(b-a);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	int x, y;
	pt a, b;
	pt center;
	int area, radius;
	ld base, height;

	int T;
	cin >> T;
	while (T--) {
		cin >> area;
		cin >> x >> y >> radius;
		center = pt(x,y);
		cin >> x >> y;
		a = pt(x,y) - center;
		cin >> x >> y;
		b = pt(x,y) - center;

		if (a.imag() == b.imag()) {
			a = pt(a.imag(), a.real());
			b = pt(b.imag(), b.real());
		}

		complex<ll> aa(llround(a.real()), llround(a.imag()));
		complex<ll> bb(llround(b.real()), llround(b.imag()));

		int ans = 0;
		base = abs(a-b);
		height = area/base;

		if (a.real() == b.real()) {
			if (abs(height - llround(height)) < EPS) {
				ld shift, top; 
				ll truncated;

				shift = a.real() + height;
				if (shift < radius + EPS) {
					top = sqrt(sqr(radius) - sqr(shift));
					truncated = top + EPS;
					ans += 2*truncated + 1;
				}

				shift = a.real() - height;
				if (shift < radius + EPS) {
					top = sqrt(sqr(radius) - sqr(shift));
					truncated = top + EPS;
					ans += 2*truncated + 1;
				}
			}
		}

		else {
			ld slope = (a.imag() - b.imag()) / (a.real() - b.real());
			ld hypo = sqrt(sqr(slope) + 1);
			ld vdiff = height * hypo;

			ll vcount = abs(aa.real() - bb.real()) / abs(__gcd(aa.real() - bb.real(), aa.imag() - bb.imag()));
			//cerr << "vcount: " << vcount << nl;
			if (abs((vdiff*vcount) - llround(vdiff*vcount)) < EPS) {
				ld shift, horiz;
				pt mid, left, right;
				ld ldist, rdist;
				ll truncleft, truncright;

				shift = abs(lp_dist(a + pt(0,vdiff), b + pt(0,vdiff), pt(0,0)));
				if (shift < radius + EPS) {
					mid = pt(-slope * shift/hypo, shift/hypo);
					horiz = sqrt(sqr(radius) - sqr(shift));
					left = mid - horiz/hypo * pt(1,slope);
					right = mid + horiz/hypo * pt(1,slope);
					ldist = min(left.real(), right.real());
					rdist = max(left.real(), right.real());
					truncright = floor((rdist + EPS)/vcount);
					truncleft = floor((-ldist + EPS)/vcount);
					truncleft *= -1;
					ans += abs(truncright - truncleft + 1);
					//cerr << left << " -- " << right << " --> " << ldist << " and " << rdist << " --> truncated " << truncleft << " " << truncright << nl;
				}

				shift = abs(lp_dist(a - pt(0,vdiff), b - pt(0,vdiff), pt(0,0)));
				if (shift < radius + EPS) {
					mid = pt(-slope * shift/hypo, shift/hypo);
					horiz = sqrt(sqr(radius) - sqr(shift));
					left = mid - horiz/hypo * pt(1,slope);
					right = mid + horiz/hypo * pt(1,slope);
					ldist = min(left.real(), right.real());
					rdist = max(left.real(), right.real());
					truncright = floor((rdist + EPS)/vcount);
					truncleft = floor((-ldist + EPS)/vcount);
					truncleft *= -1;
					ans += abs(truncright - truncleft + 1);
					//cerr << left << " -- " << right << " --> " << ldist << " and " << rdist << " --> truncated " << truncleft << " " << truncright << nl;
				}
			}
		}

		cout << ans << nl;
	}

	return 0;
}
