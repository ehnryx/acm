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

template <class T, class U>
ostream& operator << (ostream& os, const pair<T,U>& v) {
	return os << '(' << v.first << ',' << v.second << ')';
}

////////////////////////////////////////////////////////////////////////
// Rational struct (UNTESTED)
//*!
struct Frac {
    ll n, d;
	Frac(ll a=0, ll b=1) {
		if (b) {
			ll g = __gcd(a,b);
			n = a/g; d = b/g;
			if (d<0) { n = -n; d = -d; }
		} else {
			n = (a ? a/abs(a) : 0);
			d = 0;
		}
	}
    friend ostream& operator << (ostream& os, const Frac& f) {
        return os << '(' << f.n << '/' << f.d << ')';
    }
    operator ld() { return (ld)n/d; }
    Frac operator + (const Frac& f) const { return Frac(n*f.d + d*f.n, d*f.d); }
    Frac operator - (const Frac& f) const { return Frac(n*f.d - d*f.n, d*f.d); }
    Frac operator * (const Frac& f) const { return Frac(n*f.n, d*f.d); }
    Frac operator / (const Frac& f) const { return Frac(n*f.d, d*f.n); }
    bool operator == (const Frac& f) const {
        if (!n && !d) return false;
        if (!f.n && !f.d) return false;
        return n==f.n && d==f.d;
    }
    bool operator < (const Frac& f) const {
        if (!n && !d) return false;
        if (!f.n && !f.d) return true;
        return n*f.d < d*f.n;
    }
};
//*/

struct Segment {
	pii a, b;
	Segment(pii a, pii b): a(a), b(b) {}
	bool operator < (const Segment& o) const {
		if (a!=o.a) return a<o.a;
		else return b<o.b;
	}
	bool operator == (const Segment& o) const {
		return a == o.a && b == o.b;
	}
	bool operator != (const Segment& o) const {
		return a != o.a || b != o.b;
	}
	pii start() const { return min(a,b); }
	pii end() const { return max(a,b); }
	pair<Frac,Frac> line() const {
		if (a.first == b.first) {
			return pair<Frac,Frac>(Frac(1,0), Frac(a.first,1));
		} else {
			Frac m(a.second-b.second,a.first-b.first);
			Frac y = Frac(a.second,1) - m*Frac(a.first,1);
			return pair<Frac,Frac>(m,y);
		}
	}
	friend ostream& operator << (ostream& os, const Segment& s) {
		return os << '(' << s.a.first << ',' << s.a.second << ") -- ("
			<< s.b.first << ',' << s.b.second << ')';
	}
};

ll area(const vector<pii>& p) {
	return (ll)p[0].first*p[1].second - (ll)p[0].second*p[1].first
		+ (ll)p[1].first*p[2].second - (ll)p[1].second*p[2].first
		+ (ll)p[2].first*p[0].second - (ll)p[2].second*p[0].first;
}

vector<Segment> solve(const vector<Segment> segs) {
	map<pair<Frac,Frac>,vector<pair<pii,int>>> lines;
	for (const Segment& it : segs) {
		pair<Frac,Frac> key = it.line();
		lines[key].push_back(pair<pii,int>(it.start(), 1));
		lines[key].push_back(pair<pii,int>(it.end(), -1));
	}

	vector<Segment> out;
	for (auto& line : lines) {
		//cerr << "  line: " << "y = " << line.first.first << "x + " << line.first.second << nl;
		sort(line.second.begin(), line.second.end());
		int cur = 0;
		pii pre(INF,INF);
		for (const pair<pii,int>& it : line.second) {
			//cerr << "    @ " << it.first << " w/ " << it.second << nl;
			if (cur == 1 && pre != it.first) {
				if (out.empty() || out.back().b != pre) {
					//cerr << "      add segment " << pre << " -> " << it.first << nl;
					out.push_back(Segment(pre, it.first));
				} else {
					//cerr << "      update " << out.back().a << " -> " << it.first << nl;
					out.back().b = it.first;
				}
			}
			cur += it.second;
			pre = it.first;
		}
	}
	return out;
}

//#define FILEIO
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);
	////cerr << fixed << setprecision(10);
#ifdef FILEIO
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#endif

	vector<Segment> segs[2];
	for (int r=0; r<2; r++) {
		int n, x, y;
		cin >> n;
		for (int i=0; i<n; i++) {
			vector<pii> p;
			for (int j=0; j<3; j++) {
				cin >> x >> y;
				p.push_back(pii(x,y));
			}
			for (int j=0; j<3; j++) {
				segs[r].push_back(Segment(p[j],p[(j+1)%3]));
			}
		}
		//cerr << nl;
		//cerr << "SOLVE " << r << nl;
		segs[r] = solve(segs[r]);
	}

	//cerr << nl;
	//cerr << "segs[0]: " << segs[0].size() << nl; for (const Segment& it:segs[0]) //cerr << it << nl;
	//cerr << nl;
	//cerr << "segs[1]: " << segs[1].size() << nl; for (const Segment& it:segs[1]) //cerr << it << nl;
	//cerr << nl;

	if (segs[0].size() != segs[1].size()) {
		cout << "no" << nl;
		return 0;
	} else {
		sort(segs[0].begin(), segs[0].end());
		sort(segs[1].begin(), segs[1].end());
		for (int i=0; i<segs[0].size(); i++) {
			if (segs[0] != segs[1]) {
				cout << "no" << nl;
				return 0;
			}
		}
		cout << "yes" << nl;
		return 0;
	}

	return 0;
}
