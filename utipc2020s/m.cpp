#pragma GCC optimize("O3")
#pragma GCC optimize("fast-math")
#pragma GCC optimize("cx-limited-range")
#include <bits/stdc++.h>
using namespace std;

const char nl = '\n';
typedef long long ll;
typedef long double ld;
typedef complex<ld> pt;

const ld EPS = 1e-9;

ld cp(const pt& a, const pt& b) {
	return imag(conj(a) * b);
}

ld dp(const pt& a, const pt& b) {
	return real(conj(a) * b);
}

bool eq(const pt& a, const pt& b) {
	return abs(a-b) < EPS;
}

bool cmp_lex_i(const pt& a, const pt& b) {
	return a.imag() < b.imag()-EPS || (a.imag() <= b.imag()+EPS && a.real() < b.real()-EPS);
}

pt line_inter(const pt& a, const pt& b, const pt& c, const pt& d) {
	return a + cp(c-a, d-c) / cp(b-a, d-c) * (b-a);
}

bool on_segment(const pt& a, const pt& b, const pt& p) {
	if(eq(a, p) || eq(b, p)) return true;
	return abs(cp(b-a, p-a)) / abs(b-a) < EPS && dp(b-a, p-a) > 0 && dp(a-b, p-b) > 0;
}

bool on_boundary(const vector<pt>& v, const pt& p) {
	bool res = false;
	for(int i=v.size()-1, j=0; j<v.size(); i=j++) {
		res |= on_segment(v[i], v[j], p);
	}
	return res;
}

bool pt_in_polygon(const vector<pt>& v, const pt& p, bool strict) {
	if(on_boundary(v, p)) return !strict;
	ld res = 0;
	for(int i=v.size()-1, j=0; j<v.size(); i=j++) {
		res += atan2(cp(v[i]-p, v[j]-p), dp(v[i]-p, v[j]-p));
	}
	return abs(res) > 1;
}

vector<pt> chull(vector<pt> p) {
	sort(p.begin(), p.end(), cmp_lex_i); int top=0, bot=1;
	vector<pt> ch(2*p.size());
	for(int i=0, d=1; i<p.size() && i>=0; i+=d) {
		while(top > bot && cp(ch[top-1]-ch[top-2], p[i]-ch[top-2]) <= 0) top--;
		ch[top++] = p[i]; if(i == p.size()-1) d = -1, bot = top;
	}
	ch.resize(max(1, top-1)); return ch;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);

	int l, w;
	cin >> l >> w;
	int n, m;
	cin >> n >> m;
	vector<pair<pt,pt>> segs;
	for(int i=0; i<n; i++) {
		int a, b, x, y;
		cin >> a >> b >> x >> y;
		segs.emplace_back(pt(a, b), pt(x, y));
	}

	while(m--) {
		int a, b, x, y;
		cin >> a >> b >> x >> y;
		vector<pt> r = {
			pt(a, b),
			pt(a, y),
			pt(x, y),
			pt(x, b),
		};
		vector<pt> v;
		for(int k=0; k<n; k++) {
			for(int i=4-1, j=0; j<4; i=j++) {
				pt it = line_inter(r[i], r[j], segs[k].first, segs[k].second);
				if(on_segment(r[i], r[j], it)) {
					v.push_back(it);
				}
			}
		}
		v = chull(v);
		pt center = accumulate(r.begin(), r.end(), pt(0,0)) / (ld)4;
		if(pt_in_polygon(v, center, false)) {
			cout << "No" << nl;
		} else {
			cout << "Yes" << nl;
		}
	}

	return 0;
}
