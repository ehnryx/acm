#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;
typedef pair<ld,ld> pdd;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

ld cp(const pt& a, const pt& b) { return imag(conj(a)*b); }
ld area(const pol& v) { return cp(v[1]-v[0], v[2]-v[0]); }
bool eq(const pt& a, const pt& b) { return abs(a-b) < EPS; }

struct ppt {
	pt a, b;
	ppt(const pt& a, const pt& b): a(a), b(b) {}
	bool operator != (const ppt& o) const {
		return !eq(a,o.a) || !eq(b,o.b);
	}
	bool operator < (const ppt& o) const {
		if (abs(a.real()-o.a.real()) > EPS) return a.real() < o.a.real();
		if (abs(a.imag()-o.a.imag()) > EPS) return a.imag() < o.a.imag();
		if (abs(b.real()-o.b.real()) > EPS) return b.real() < o.b.real();
		else return b.imag() < o.b.imag();
	}
};

vector<ppt> solve(const vector<ppt>& seg) {
	map<pdd,vector<pair<ld,int>>> line;
	for (const ppt& it : seg) {
		if (it.a.real() == it.b.real()) {
			ld s = it.a.imag();
			ld t = it.b.imag();
			line[pdd(1e42,it.a.real())].push_back(pair<ld,int>(s, 1));
			line[pdd(1e42,it.a.real())].push_back(pair<ld,int>(t, -1));
		} else {
			ld m = (it.a.imag()-it.b.imag()) / (it.a.real()-it.b.real());
			ld b = it.a.imag() - m*it.a.real();
			ld s = it.a.real();
			ld t = it.b.real();
			line[pdd(m,b)].push_back(pair<ld,int>(s, 1));
			line[pdd(m,b)].push_back(pair<ld,int>(t, -1));
		}
	}

	vector<ppt> out;
	for (auto& it : line) {
		ld m = it.first.first;
		ld b = it.first.second;
		sort(it.second.begin(), it.second.end());
		//cerr << "  line: " << m << " " << b << nl;

		int cnt = 0;
		pt p;
		for (const auto& val : it.second) {
			pt c;
			if (m == 1e42) {
				c = pt(b, val.first);
			} else {
				c = pt(val.first, m*val.first + b);
			}
			//cerr << "    " << val.first << " -> " << c << " w/ cnt " << cnt << nl;

			assert(abs(cnt) <= 2);
			if (abs(cnt) == 1) {
				if (!out.empty() && eq(out.back().b, p)) {
					out.back().b = c;
					//cerr << "    " << "extend seg: " << out.back().a << " " << p << " -> " << c << nl;
				} else if (!eq(p,c)) {
					out.push_back(ppt(p, c));
					//cerr << "    " << "add seg: " << p << " " << c << nl;
				}
			}
			cnt += val.second;
			p = c;
		}
	}
	return out;
}

//#define FILEIO
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);
	//cerr << fixed << setprecision(10);
#ifdef FILEIO
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#endif

	vector<ppt> seg[2];
	for (int r=0; r<2; r++) {
		//cerr << nl;
		//cerr << "polygon " << r << nl;
		int n, x, y;
		cin >> n;
		for (int i=0; i<n; i++) {
			vector<pt> p;
			for (int j=0; j<3; j++) {
				cin >> x >> y;
				p.push_back(pt(x,y));
			}
			//cerr << "  area: " << area(p) << nl;
			if (area(p) < 0) reverse(p.begin(), p.end());
			for (int j=0; j<3; j++) {
				seg[r].push_back(ppt(p[j], p[(j+1)%3]));
				//cerr << "  add seg " << p[j] << " " << p[(j+1)%3] << nl;
			}
		}
		//cerr << nl;
		//cerr << "SOLVE " << r << nl;
		/*
		seg[r] = solve(seg[r]);
		sort(seg[r].begin(), seg[r].end());
		*/
		auto tmp = solve(seg[r]);
		seg[r].clear();
		for (int i = 0; i < tmp.size(); i++) {
			if (i+1 == tmp.size() || tmp[i] != tmp[i+1]) {
				seg[r].push_back(tmp[i]);
			} else {
				i++;
			}
		}
	}

	//cerr << nl;
	//cerr << "seg[0]: " << seg[0].size() << nl; for (const ppt& it : seg[0]) //cerr << it.a << " " << it.b << nl;
	//cerr << "seg[1]: " << seg[1].size() << nl; for (const ppt& it : seg[1]) //cerr << it.a << " " << it.b << nl;
	if (seg[0].size() != seg[1].size()) {
		cout << "no" << nl;
		return 0;
	}
	for (int i=0; i<seg[0].size(); i++) {
		if (seg[0][i] != seg[1][i]) {
			cout << "no" << nl;
			return 0;
		}
	}
	cout << "yes" << nl;

	return 0;
}
