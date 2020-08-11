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

const int N = 1<<19;
ll segt[2*N];
void update(int x, ll v) {
	for (x += N, segt[x] = max(segt[x], v); x>1; x/=2) {
		segt[x/2] = max(segt[x], segt[x^1]);
	}
}
ll query(int l, int r) {
	ll res = 0;
	for (l+=N, r+=N+1; l<r; l/=2, r/=2) {
		if (l&1) res = max(res, segt[l++]);
		if (r&1) res = max(res, segt[--r]);
	}
	return res;
}

struct Point {
	int x, y, dmg;
	int px, py, t;
	Point(int i, int c, int d, int r): t(r) {
		dmg = d;
		if (r == 2) {
			px = py = x = y = i;
			if (c != 1) dmg = 0;
		} else if (r == 1) {
			tie(px, py) = pii(i-c+1, i);
			tie(x, y) = pii(i-c+1, i-1);
		} else {
			tie(px, py) = pii(i, i+c-1);
			tie(x, y) = pii(i+1, i+c-1);
		}
	}
	bool valid(int n) const {
		int minv = min(min(x,y),min(px,py));
		int maxv = max(max(x,y),max(px,py));
		return 0<minv && maxv<=n && x<=y && px<=py;
	}
	bool operator < (const Point& o) const {
		if (x != o.x) return x < o.x;
		if (t != o.t) return t < o.t;
		if (t == 0) return y < o.y;
		else return y > o.y;
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

	int n;
	cin >> n;

	int idx[n+1], dmg[n+1];
	for (int i=1; i<=n; i++) {
		cin >> idx[i];
	}
	for (int i=1; i<=n; i++) {
		cin >> dmg[i];
	}

	vector<Point> pts;
	for (int i=1; i<=n; i++) {
		Point left(i, idx[i], dmg[i], 0);
		Point right(i, idx[i], dmg[i], 1);
		if (left.valid(n)) pts.push_back(left);
		if (right.valid(n)) pts.push_back(right);
		pts.push_back(Point(i, idx[i], dmg[i], 2));
	}
	sort(pts.begin(), pts.end());

	update(n, 0);
	for (const Point& p : pts) {
		if (p.t == 1) {
			update(p.y, query(p.y+1, n) + p.dmg);
		} else {
			update(p.y, query(p.y, n) + p.dmg);
		}
	}

	for (int i=1; i<=n; i++) {
		cout << query(i,i) << " ";
	}
	cout << nl;

	return 0;
}
