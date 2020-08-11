//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;
typedef double ld;
typedef complex<ld> pt;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 998244353;
const ld EPS = 1e-11;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

ld cp(const pt& a, const pt& b) {
	return imag(conj(a) * b);
}

int sgn(const ld& x) {
	return abs(x)<EPS ? 0 : x<0 ? -1 : 1;
}

bool eq(const pt& a, const pt& b) {
	return abs(a-b) < EPS;
}

bool cmp_lex(const pt& a, const pt& b) {
	return a.real()<b.real()-EPS || (a.real()<b.real()+EPS && a.imag()<b.imag()-EPS);
}

struct Line {
	ld m, b; pt s, t;
	Line(const pt& u, const pt& v): s(u), t(v) {
		if(s.real() > t.real()) swap(s, t);
		m = (u.imag()-v.imag()) / (u.real()-v.real());
		b = u.imag() - m*u.real();
	}
	bool operator < (const Line& o) const {
		ld l = max(s.real(), o.s.real());
		ld r = min(t.real(), o.t.real());
		ld x = (l+r) / 2;
		ld y = eval(x);
		ld oy = o.eval(x);
		if(abs(y-oy) > EPS) return y < oy;
		return t.real() < o.t.real();
	}
	ld eval(const ld& x) const {
		return m*x + b;
	}
};

bool intersect(const Line& u, const Line& v) {
	pt a = u.s, b = u.t, c = v.s, d = v.t;
	ld ab = abs(a-b), cd = abs(c-d);
	int s1 = sgn(cp(a-b, c-b) / ab);
	int s2 = sgn(cp(a-b, d-b) / ab);
	int s3 = sgn(cp(c-d, a-d) / cd);
	int s4 = sgn(cp(c-d, b-d) / cd);
	if(s1 == 0 && s2 == 0 && s3 == 0) {
		if(cmp_lex(b, a)) swap(a, b);
		if(cmp_lex(d, c)) swap(c, d);
		return cmp_lex(a, d) && cmp_lex(c, b);
	} else if(eq(a, c) || eq(a, d) || eq(b, c) || eq(b, d)) {
		return false;
	} else {
		return s1*s2 <= 0 && s3*s4 <= 0;
	}
}

bool is_polygon(vector<pt> p) {
	int n = p.size();
	pt rot = exp(pt(0, 1.789));
	for(pt& v : p) {
		v *= rot;
	}

	vector<pair<ld,int>> ev;
	for(int j=n-1, i=0; i<n; j=i++) {
		ld s = min(p[i].real(), p[j].real());
		ld t = max(p[i].real(), p[j].real());
		assert(abs(s-t) > 7*EPS);
		ev.emplace_back(s, j);
		ev.emplace_back(t, j);
	}
	sort(ev.begin(), ev.end());

	vector<bool> in_set(n);
	set<Line> active;
	for(auto [_, i] : ev) {
		Line cur(p[i], p[(i+1)%n]);
		if(in_set[i]) {
			auto it = active.erase(active.find(cur));
			if(it != active.begin() && it != active.end() && intersect(*it, *prev(it))) {
				return false;
			}
		} else {
			in_set[i] = true;
			auto [it, ok] = active.insert(cur);
			if(!ok) return false;
			if(it != active.begin() && intersect(*it, *prev(it))) {
				return false;
			}
			if(next(it) != active.end() && intersect(*it, *next(it))) {
				return false;
			}
		}
	}
	return true;
}

// TODO
// double-check correctness
// read limits carefully
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	for(int n; cin >> n && n; ) {
		set<pair<int,int>> seen;
		vector<pt> p;
		bool ok = true;
		for(int i=0; i<n; i++) {
			int x, y;
			cin >> x >> y;
			p.push_back(pt(x, y));
			ok &= seen.insert(make_pair(x, y)).second;
		}
		if(ok && is_polygon(p)) {
			cout << "YES" << nl;
		} else {
			cout << "NO" << nl;
		}
	}

	return 0;
}
