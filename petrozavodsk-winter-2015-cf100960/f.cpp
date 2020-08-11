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

ld cp(const pt& a, const pt& b) { return imag(conj(a)*b); }
ld sgn(const ld& x) { return x < -EPS ? -1 : x > EPS ? 1 : 0; }
ld lp_dist(const pt& a, const pt& b, const pt& p) {
	return cp(b-a, p-a) / abs(b-a);
}
pt line_inter(const pt& a, const pt& b, const pt& c, const pt& d) {
	return a + cp(c-a, d-c) / cp(b-a, d-c) * (b-a);
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

	int T;
	cin >> T;
	while (T--) {
		int ray, guard;
		cin >> ray >> guard;
		vector<pt> p;
		for (int i=0; i<3; i++) {
			int x, y;
			cin >> x >> y;
			p.push_back(pt(x,y));
		}

		// all collinear
		if (abs(cp(p[2]-p[0], p[1]-p[0])) < EPS) {
			ld len = max(abs(p[2]-p[0]), max(abs(p[1]-p[0]), abs(p[1]-p[2])));
			if (len < max(ray,guard)+EPS) {
				cout << "YES" << nl;
			} else {
				cout << "NO" << nl;
			}
		}

		// not all collinear
		else {
			bool ok = false;
			for (int i=0,j=2; i<3; j=i++) {
				int k = (i+1)%3;
				ld len = abs(p[i]-p[j]);
				pt base = line_inter(p[i], p[j], p[k], p[k] + (p[i]-p[j])*pt(0,1));
			}
			if (ok) {
				cout << "YES" << nl;
			} else {
				cout << "NO" << nl;
			}
		}
	}

	return 0;
}
