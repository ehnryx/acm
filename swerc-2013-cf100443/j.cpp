//#pragma GCC optimize("O3")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
//#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const ld dx = 9e-3;

struct Circle {
	int x, y, r, sign;
	inline pair<ld,ld> query(const ld& v) const {
		ld dsqr = r*r - (x-v)*(x-v);
		if (dsqr < EPS) return pair<ld,ld>(0,0);
		dsqr = sqrt(dsqr);
		return pair<ld,ld>(y-dsqr, y+dsqr);
	}
};

const int N = 1e4;
pair<ld,int> p[N];
Circle circ[N];
pii ep[N];
pii vals[N];

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
		int numcirc = 0;
		int epcnt = 0;
		for (int i=0; i<n; i++) {
			cin >> x >> y >> a >> b;
			circ[numcirc++] = Circle{x,y,a+b,1};
			if (a-b > 0) circ[numcirc++] = Circle{x,y,a-b,-1};
			ep[epcnt++] = pii(max(-1000,x-a-b),1);
			ep[epcnt++] = pii(min(1000,x+a+b),-1);
		}
		sort(ep, ep+epcnt);

		int pre;
		int cnt = 0;
		int vcnt = 0;
		for (int i=0; i<epcnt; i++) {
			if (cnt == 0) {
				pre = ep[i].first;
			}
			cnt += ep[i].second;
			if (cnt == 0) {
				vals[vcnt++] = pii(pre, ep[i].first);
			}
		}

		ld ans = 0;
		for (int j=0; j<vcnt; j++) {
			for (ld x = vals[j].first+dx/2; x < vals[j].second; x += dx) {
				int id = 0;
				for (int i = 0; i < numcirc; i++) {
					const Circle& c = circ[i];
					if (abs(c.x-x) > c.r) continue;
					ld s, t;
					tie(s,t) = c.query(x);
					if (s != t) {
						p[id++] = pair<ld,int>(s, c.sign);
						p[id++] = pair<ld,int>(t, -c.sign);
					}
				}
				sort(p, p+id);

				int cnt = 1;
				for (int i=1; i<id; i++) {
					if (cnt > 0) {
						ans += p[i].first-p[i-1].first;
					}
					cnt += p[i].second;
				}
			}
		}
		cout << "Case " << num << ": " << ans*dx << nl;
	}

	return 0;
}
