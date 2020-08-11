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
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

struct Point {
	pt x; int id;
	bool operator < (const Point& o) const {
		if (x.real() == o.x.real()) return x.imag() < o.x.imag();
		else return x.real() < o.x.real();
	}
};

ld cp(const pt& a, const pt& b) { return imag(conj(a)*b); }

pt base;
bool neg;
bool cmp(const Point& a, const Point& b) {
	return neg ^ (cp(a.x-base, b.x-base) > 0);
}

//#define FILEIO
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);
#ifdef FILEIO
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#endif

	int n;
	cin >> n;

	int x, y;
	vector<Point> p;
	for (int i=1; i<=n; i++) {
		cin >> x >> y;
		p.push_back({pt(x,y),i});
	}
	sort(p.begin(), p.end());

	string s;
	cin >> s;
	s = "L" + s;
	for (int i=1; i<n; i++) {
		base = p[i-1].x;
		if (s[i] == 'L') {
			neg = false;
			sort(p.begin()+i, p.end(), cmp);
		} else {
			neg = true;
			sort(p.begin()+i, p.end(), cmp);
		}
	}
	for (const Point& v : p) {
		cout << v.id << " ";
	}
	cout << nl;

	return 0;
}
