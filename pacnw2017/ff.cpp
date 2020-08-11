#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
#define nl '\n'

const ll INF = 0x3f3f3f3f;
const ll MOD = 1e9+7;
//const ld EPS = 1e-13;

struct Frac {
	ll n, d;
	Frac(): n(0), d(1) {}
	Frac(ll x, ll y) {
		ll g = __gcd(x,y);
		if (g == 0) n = 0, d = 1;
		else { 
			n = x/g, d = y/g;
			if (d < 0) n = -n, d = -d;
		}
	}
	Frac operator * (const Frac& f) const { return Frac(n*f.n, d*f.d); }
	Frac operator / (const Frac& f) const { return Frac(n*f.d, d*f.n); }
	Frac operator + (const Frac& f) const { return Frac(n*f.d + f.n*d, d*f.d); }
	Frac operator - (const Frac& f) const { return Frac(n*f.d - f.n*d, d*f.d); }
	Frac operator - () const { return Frac(-n, d); }
	bool operator < (const Frac& f) const { return n*f.d < f.n*d; }
	bool operator == (const Frac& f) const { return n*f.d == f.n*d; }
	bool operator != (const Frac& f) const { return !(*this == f); }
};

struct pt {
	Frac x, y;
	pt(Frac x, Frac y): x(x), y(y) {}
	pt(int a, int b) {
		x = Frac(a,1);
		y = Frac(b,1);
	}
	Frac real() const { return x; }
	Frac imag() const { return y; }
	pt operator * (const pt& p) const { return pt(x*p.x-y*p.y, x*p.y+p.x*y); }
	pt operator + (const pt& p) const { return pt(x+p.x, y+p.y); }
	pt operator - (const pt& p) const { return pt(x-p.x, y-p.y); }
	pt operator - () const { return pt(-x, -y); }
};

ostream& operator << (ostream& os, const Frac& f) {
	os << f.n << "/" << f.d; return os;
}
ostream& operator << (ostream& os, const pt& p) {
	os << "(" << p.x << "," << p.y << ")"; return os;
}

pt operator * (const Frac& f, const pt& p) {
	return pt(f*p.x, f*p.y);
}

Frac sqr(const Frac& f) { return f*f; }
Frac abs(const pt& p) { return sqr(p.real()) + sqr(p.imag()); }
Frac imag(const pt& p) { return p.imag(); }
Frac real(const pt& p) { return p.real(); }
pt conj(const pt& p) { return pt(p.real(), -p.imag()); }

Frac cp(const pt& a, const pt& b) { return imag(conj(a)*b); }
inline pt line_inter(const pt& a, const pt& b, const pt& c, const pt& d) {
	return a + cp(c-a, d-c) / cp(b-a, d-c) * (b-a);
}

int count(int n, const pt& center, const vector<pt>& p) {
	set<Frac> dists;
	for (int i = 0; i < n; i++) {
		Frac dist = abs(p[i]-center);
		auto it = dists.lower_bound(dist);
		if (it == dists.end() || *it != dist) {
			if (it == dists.begin() || *(--it) != dist) {
				dists.insert(dist);
			}
		}
	}
	return dists.size();
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	int x, y;
	int n;
	cin >> n;
	vector<pt> p;
	for (int i = 0; i < n; i++) {
		cin >> x >> y;
		p.push_back(pt(x,y));
	}

	int ans = INF;
	if (n < 3) {
		ans = 1;
	} else {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < i; j++) {
				ans = min(ans, count(n, Frac(1,2)*(p[i]+p[j]), p));
			}
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < i; j++) {
				for (int k = 0; k < n; k++) {
					for (int l = 0; l < k; l++) {
						if (cp(p[i]-p[j], p[k]-p[l]) != Frac(0,1)) {
							pt perp1 = pt(0,1)*(p[i]-p[j]);
							pt perp2 = pt(0,1)*(p[k]-p[l]);
							pt mid1 = Frac(1,2)*(p[i]+p[j]);
							pt mid2 = Frac(1,2)*(p[k]+p[l]);
							pt center = line_inter(perp1+mid1, mid1, perp2+mid2, mid2);
							ans = min(ans, count(n, center, p));
						}
					}
				}
			}
		}
	}
	cout << ans << nl;

	return 0;
}
