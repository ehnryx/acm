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

const ld dx = 3e-3;

struct Circle {
	int x, y, r, sign;
	pair<ld,ld> query(const ld& v) const {
		ld dsqr = r*r - (x-v)*(x-v);
		if (dsqr < EPS) return pair<ld,ld>(0,0);
		dsqr = sqrt(dsqr);
		return pair<ld,ld>(y-dsqr, y+dsqr);
	}
};

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

	for (int num=1; num<=T; num++) {
		int n, x, y, a, b;
		cin >> n;
		vector<Circle> circ;
		for (int i=0; i<n; i++) {
			cin >> x >> y >> a >> b;
			circ.push_back({x,y,a+b,1});
			if (a-b > 0) circ.push_back({x,y,a-b,-1});
		}

		ld ans = 0;
		for (ld x = -1000+dx/2; x < 1000; x += dx) {
			vector<pair<ld,int>> p;
			for (const Circle& c : circ) {
				ld s, t;
				tie(s,t) = c.query(x);
				if (s != t) {
					p.emplace_back(s, c.sign);
					p.emplace_back(t, -c.sign);
				}
			}
			sort(p.begin(), p.end());

			ld pre = 0;
			int cnt = 0;
			for (const pair<ld,int>& it : p) {
				if (cnt > 0) {
					ans += it.first-pre;
				}
				pre = it.first;
				cnt += it.second;
			}
		}
		cout << "Case " << num << ": " << ans*dx << nl;
	}

	return 0;
}
