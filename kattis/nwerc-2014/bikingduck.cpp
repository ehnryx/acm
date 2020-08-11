#pragma GCC optimize("O3")
#pragma GCC optimize("fast-math")
//#pragma GCC target("sse4,avx2,abm,fma")
#include <bits/stdc++.h>
using namespace std;

typedef double ld;
typedef complex<ld> pt;

const char nl = '\n';

const int M = 36;

ld dot_dot(const pt& s, const pt& t, const pt& a, const pt& b, const ld& walk, const ld& bike) {
	return (abs(s-a) + abs(b-t)) / walk + abs(a-b) / bike;
}

ld dot_edge(const pt& s, const pt& t, const pt& p, const pt& a, const pt& b, const ld& walk, const ld& bike) {
	ld l = 0;
	ld r = 1;
	for(int bs=0; bs<M; bs++) {
		ld lm = (9*l + 8*r) / 17;
		ld rm = (8*l + 9*r) / 17;
		pt lp = lm*a + (1-lm)*b;
		pt rp = rm*a + (1-rm)*b;
		if(dot_dot(s, t, p, lp, walk, bike) < dot_dot(s, t, p, rp, walk, bike)) {
			r = rm;
		} else {
			l = lm;
		}
	}
	pt o = r*a + (1-r)*b;
	return dot_dot(s, t, p, o, walk, bike);
}

ld edge_edge(const pt& s, const pt& t, const pt& a, const pt& b, const pt& c, const pt& d, const ld& walk, const ld& bike) {
	ld l = 0;
	ld r = 1;
	for(int bs=0; bs<M; bs++) {
		ld lm = (9*l + 8*r) / 17;
		ld rm = (8*l + 9*r) / 17;
		pt lp = lm*a + (1-lm)*b;
		pt rp = rm*a + (1-rm)*b;
		if(dot_edge(s, t, lp, c, d, walk, bike) < dot_edge(s, t, rp, c, d, walk, bike)) {
			r = rm;
		} else {
			l = lm;
		}
	}
	pt p = r*a + (1-r)*b;
	return dot_edge(s, t, p, c, d, walk, bike);
}

// TODO
// double-check correctness
// read limits carefully
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	int walk, bike;
	cin >> walk >> bike;

	int left, right, bot, top;
	cin >> left >> bot >> right >> top;
	vector<pt> rect {
		pt(left, bot),
		pt(right, bot),
		pt(right, top),
		pt(left, top),
	};

	int sx, sy;
	cin >> sx >> sy;
	pt s(sx, sy);

	int tx, ty;
	cin >> tx >> ty;
	pt t(tx, ty);

	int n;
	cin >> n;
	vector<pt> b;
	for(int i=0; i<n; i++) {
		int x, y;
		cin >> x >> y;
		b.emplace_back(x, y);
	}

	// S -> T
	ld ans = abs(s-t) / (ld)walk;

	// S -> dot -> dot -> T
	for(int i=0; i<n; i++) {
		for(int j=0; j<n; j++) {
			ans = min(ans, dot_dot(s, t, b[i], b[j], walk, bike));
		}
	}

	// S -> dot -> edge -> T
	for(int i=4-1, j=0; j<4; i=j++) {
		for(int k=0; k<n; k++) {
			ans = min(ans, dot_edge(s, t, b[k], rect[i], rect[j], walk, bike));
			ans = min(ans, dot_edge(t, s, b[k], rect[i], rect[j], walk, bike));
		}
	}

	// S -> edge -> edge -> T
	for(int i=4-1, j=0; j<4; i=j++) {
		for(int ii=4-1, jj=0; jj<4; ii=jj++) {
			ans = min(ans, edge_edge(s, t, rect[i], rect[j], rect[ii], rect[jj], walk, bike));
		}
	}

	cout << ans << nl;

	return 0;
}
