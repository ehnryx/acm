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
	int x, y;
	bool top;
	Point(){}
	Point(int x, int y, bool t): x(x), y(y), top(t) {}
	bool operator < (const Point& v) const {
		if (x == v.x) return top < v.top;
		else return x < v.x;
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);

	int n, m;
	cin >> n >> m;

	int x, y, lb, ub;
	vector<Point> p;

	cin >> lb;
	for (int i = 0; i < n; i++) {
		cin >> x >> y;
		p.push_back(Point(x,y, false));
	}

	cin >> ub;
	for (int i = 0; i < m; i++) {
		cin >> x >> y;
		p.push_back(Point(x,y, true));
	}

	sort(p.begin(), p.end());

	ll ans = 0;
	ll cur = 0;
	int cnt = 0;
	int prex = -INF;
	bool open = true;

	for (const Point& it : p) {
		if (lb < ub) {
			cur += (ll)(it.x-prex)*(ub-lb);
		} else {
			open = false;
		}

		if (it.top) {
			ub = it.y;
		} else {
			lb = it.y;
		}

		if (lb >= ub) {
			if (!open && cur) {
				cnt++;
				ans += cur;
				cur = 0;
			}
		}
		prex = it.x;
	}

	cout << cnt << " " << ans << nl;

	return 0;
}
