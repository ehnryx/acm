#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ld EPS = 1e-13L;
const ld PI = acos((ld)-1);

/*
struct cplx {
	ld x,y; cplx() { x=y=0; }
	cplx(ld nx, ld ny=0) { x=nx; y=ny; }
	cplx operator + (const cplx& c) const { return {x+c.x, y+c.y}; }
	cplx operator - (const cplx& c) const { return {x-c.x, y-c.y}; }
	cplx operator * (const cplx& c) const { return {x*c.x - y*c.y, x*c.y + y*c.x}; }
	cplx operator * (const ld& c) const { return {x*c,y*c}; }
	cplx operator / (const ld& c) const { return {x/c,y/c}; }
};
typedef cplx pt;
ld cp(const pt& a, const pt& b) { return a.x*b.y - b.x*a.y; }
ld norm(const pt& a) { return a.x*a.x + a.y*a.y; }
ld abs(const pt& a) { return sqrt(norm(a)); }
ld arg(const pt& a) { return atan2(a.y, a.x); }
*/

typedef complex<ld> pt;
ld cp(const pt& a, const pt& b) { return imag(conj(a)*b); }

void cc_inter_mid(pt p1, ld r1, pt p2, ld r2, pt& i1, pt& i2) {
	ld d = abs(p1-p2);
	ld l=0; ld r=r1;
	for (int i=0; i<100; i++) {
		ld x = (l+r)/2;
		ld y = abs(d-x);
		ld h1 = r1*r1 - x*x;
		ld h2 = r2*r2 - y*y;
		if (h1 > h2) l = x;
		else r = x;
	}
	ld x=(l+r)/2;
	pt c = p1 + (p2-p1)/d * x;
	ld hf = sqrt(r1*r1 - x*x)/d;
	i1 = c + (p2-p1)*pt(0,1)*hf;
	i2 = c - (p2-p1)*pt(0,1)*hf;
}

int cc_inter(pt p1, ld r1, pt p2, ld r2, pt& i1, pt& i2) {
	ld d = abs(p1-p2);
	if (r1+r2<d || abs(r1-r2)>d) return 0;
	if (r1 > r2) cc_inter_mid(p1, r1, p2, r2, i1, i2);
	else cc_inter_mid(p2, r2, p1, r1, i1, i2);
	return 2;
}

ld chord(ld s, ld t, ld r) {
	return r * sqrt(2*(1-cos(s-t)));
}

struct Point {
	ld x; int t;
	bool operator < (const Point& o) const {
		return x < o.x;
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout << fixed << setprecision(15);

	pt o(0,0);
	int cnt[3];

	int T;
	cin >> T;
	for (int testnum=1; testnum<=T; testnum++) {
		int n, r;
		cin >> n >> r;

		vector<Point> segs, range;
		for (int i=0; i<n; i++) {
			int x, y, ri;
			cin >> x >> y >> ri;
			pt c(x,y);
			pt i1, i2;
			if (cc_inter(o, r, c, ri, i1, i2) == 2) {
				if (cp(c, i1) > 0) swap(i1, i2);
				ld s = arg(i1);
				ld t = arg(i2);
				// points
				segs.push_back({s,1});
				segs.push_back({t,1});
				// range
				range.push_back({s, -1});
				range.push_back({s+2*PI, -1});
				range.push_back({s+4*PI, -1});
				range.push_back({t, 1});
				range.push_back({t+2*PI, 1});
				range.push_back({t+4*PI, 1});
				range.push_back({s+PI, -2});
				range.push_back({s+3*PI, -2});
				range.push_back({t+PI, 2});
				range.push_back({t+3*PI, 2});
			}
		}
		sort(range.begin(), range.end());

		ld ans = (segs.empty() ? 2*r : 0);
		// points
		for (int i=0; i<segs.size(); i++) {
			for (int j=0; j<i; j++) {
				ans = max(ans, chord(segs[i].x,segs[j].x,r));
			}
		}
		// ranges
		memset(cnt, 0, sizeof cnt);
		for (const Point& it : range) {
			cnt[abs(it.t)] += it.t;
			if (cnt[abs(it.t)] < 0) cnt[abs(it.t)] = 0;
			if (cnt[1] && cnt[2]) {
				ans = 2*r;
			}
		}

		cout << "Case #" << testnum << ": " << ans << nl;
	}

	return 0;
}
