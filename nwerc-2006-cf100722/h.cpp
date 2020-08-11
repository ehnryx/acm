#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef complex<ld> ppt;
#define nl '\n'

inline ld cp(const ppt& a, const ppt& b) { return imag(conj(a)*b); }
inline ppt line_inter(const ppt& a, const ppt& b, const ppt& c, const ppt& d) {
	return a + cp(c-a, d-c) / cp(b-a, d-c) * (b-a);
}

struct pt {
	ld x, y;
	pt() {}
	pt(ld a, ld b) : x(a), y(b) {}
	pt operator+ (const pt& o) const {
		return pt(x+o.x, y+o.y);
	}
	pt operator- (const pt& o) const {
		return pt(x-o.x, y-o.y);
	}
};

struct line {
	pt p1, p2;
	line() {}
	line(pt a, pt b) : p1(a), p2(b) {}
	ld solve(ld x) const {
		ld dx = x - p1.x;
		pt pp = (p2-p1);
		return pp.y*dx/pp.x+p1.y;
	}
	ld area(ld l, ld r) const {
		return (r-l) * (solve(l) + solve(r)) / 2;
	}
};

const int L = 10100;
ld height[L];
ld area[L];
pt pts[505];
line trap[L];

struct segtree {
	vector<ld> t;
	int n, h;
	segtree(int l, int r) {
		h = 32 - __builtin_clz(r+1);
		n = 1<<h;
		t = vector<ld>(n<<1, 0);
		for (int i=l; i<=r; ++i) {
			t[i+n] = height[i];
		}
		for (int i=n-1; i; --i) {
			t[i] = min(t[i<<1], t[i<<1|1]);
		}
	}
	ld query(int l, int r) { // EXCLUSIVE
		ld ans = 1e10;
		for (l+=n, r+=n; l<r; l/=2, r/=2) {
			if (l%2) ans = min(ans, t[l++]);
			if (r%2) ans = min(ans, t[--r]);
		}
		return ans;
	}


};

void solve() {
	int n, len;
	cin >> n >> len;
	for (int i=1; i<=n; ++i) {
		cin >> pts[i].x >> pts[i].y;
		pts[i].x += 1;
	}
	int start = pts[1].x;
	int fin = pts[n].x;
	area[start] = height[start-1] = 0;
	for (int i=1; i<n; ++i) {
		line lne(pts[i], pts[i+1]);
		for (int j=pts[i].x; j<=pts[i+1].x; ++j) {
			height[j] = lne.solve(j);
			if(j<pts[i+1].x) trap[j] = lne;
			//cerr << " HEIGHT " << j << " : " << height[j] << endl;
		}
	}
	for (int i=start+1; i<=fin; ++i) {
		area[i] = area[i-1] + (height[i]+height[i-1])/2;
		//cerr << " AREA " << i << " : " << area[i] << endl;
	}

	segtree st(start, fin+2);
	ld ans = 1e20;
	for (int i=start; i+len<=fin; ++i) {
		ld a = area[i+len]-area[i];
		ld mn = st.query(i, i+len+1);
		//cerr << " FROM " << i << " TO " << i+len << " GET AREA " << a << " MIN " << mn << " MIN AREA " << mn*len << endl;
		ans = min(ans, a-mn*len);
	}

	for (int i=start; i+len<fin; i++) {
		if(height[i+1]-height[i] != height[i+len+1]-height[i+len]) {
			ppt ls(i, height[i]);
			ppt lt(i+1, height[i+1]);
			ppt rs(i, height[i+len]);
			ppt rt(i+1, height[i+len+1]);
			ppt it = line_inter(ls, lt, rs, rt);
			if(i < it.real() && it.real() < i+1) {
				ld left = i+1 - it.real();
				ld right = it.real() - i;
				ld a = area[i+len]-area[i+1];
				a += trap[i].area(i+1-left, i+1);
				a += trap[i+len].area(i+len, i+len+right);
				ld mn = st.query(i+1, i+len+1);
				mn = min(mn, trap[i].solve(i+1-left));
				mn = min(mn, trap[i+len].solve(i+len+right));
				ans = min(ans, a-mn*len);
			}
		}
	}

	cout << fixed << setprecision(10) << ans << "\n";
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);

	int TT;
	cin >> TT;
	while (TT--) {
		solve();
	}

	return 0;
}
