#include <bits/stdc++.h>
using namespace std;

#define nl '\n'
typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
const int INF = 0x3f3f3f3f;

#define POINT 0
#define WALL 1
#define QUERY 2

ll sgn(ll n) {
	if (n == 0) return 0;
	return n<0 ? -1 : 1;
}

ll basex, basey;
struct Point {
	ll x, y;
	int t, id;
	bool operator < (const Point& o) const {
		ll leftn = x-basex;
		ll leftd = y-basey;
		ll rightn = o.x-basex;
		ll rightd = o.y-basey;
		if (leftd < 0) { leftn = -leftn; leftd = -leftd; }
		if (rightd < 0) { rightn = -rightn; rightd = -rightd; }
		ll left = leftn*rightd;
		ll right = leftd*rightn;
		if (left != right) return left < right;
		if (sgn(y-basey) != sgn(o.y-basey)) return sgn(y-basey) < sgn(o.y-basey);
		return abs(y-basey) < abs(o.y-basey);
	}
	bool operator > (const Point& o) const {
		ll leftn = x-basex;
		ll leftd = y-basey;
		ll rightn = o.x-basex;
		ll rightd = o.y-basey;
		if (leftd < 0) { leftn = -leftn; leftd = -leftd; }
		if (rightd < 0) { rightn = -rightn; rightd = -rightd; }
		ll left = leftn*rightd;
		ll right = leftd*rightn;
		if (left != right) return left > right;
		if (sgn(y-basey) != sgn(o.y-basey)) return sgn(y-basey) < sgn(o.y-basey);
		return abs(y-basey) < abs(o.y-basey);
	}
};

struct Wall {
	int a, b, y;
};

const int N = 4e4+1;
ll ans[N];

bool good[N];
void solve(int s, int maxy, int bm, const vector<Point>& p) {
	int goal = __builtin_popcount(bm) - 1;

	set<int> seen;
	int cnt = 0;
	for (const Point& it : p) {
		if (it.t == WALL) {
			if (bm&1<<it.id) {
				if (seen.count(it.id)) {
					seen.erase(it.id);
				} else {
					seen.insert(it.id);
				}
			}
		}
		else if (it.t == POINT) {
			if (it.y <= maxy) continue;
			//cerr << "ADD POINT " << it.x << " " << it.y << nl;
			cnt++;
		}
		else { // it.t == QUERY
			if (seen.size() == goal) {
				good[it.id] = true;
				ans[it.id] -= s*cnt;
				//cerr << "QUERY " << it.id << " -> " << cnt << nl;
			}
		}
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int n, m, q;
	cin >> n >> m >> q;

	vector<Point> points;
	vector<Point> p[10];
	for (int i=0; i<n; i++) {
		int x, y;
		cin >> x >> y;
		points.push_back({x,y,POINT});
	}

	vector<Wall> walls;
	for (int i=0; i<m; i++) {
		int a, b, y;
		cin >> a >> b >> y;
		walls.push_back({a,b,y});
		//cerr << i << ": " << a << " " << b << " " << y << nl;
	}

	for (int i=0; i<q; i++) {
		int x, y;
		cin >> x >> y;
		points.push_back({x,y,QUERY,i});
	}

	for (int i=0; i<m; i++) {
		for (const Point& it : points) {
			if (it.y == walls[i].y) continue;
			p[2*i].push_back(it);
			p[2*i+1].push_back(it);
		}
		for (int j=0; j<m; j++) {
			if (walls[i].y == walls[j].y) continue;
			p[2*i].push_back({walls[j].a,walls[j].y,WALL,j});
			p[2*i].push_back({walls[j].b,walls[j].y,WALL,j});
			p[2*i+1].push_back({walls[j].a,walls[j].y,WALL,j});
			p[2*i+1].push_back({walls[j].b,walls[j].y,WALL,j});
		}
		basey = walls[i].y;
		basex = walls[i].a;
		sort(p[2*i].begin(), p[2*i].end());
		basex = walls[i].b;
		sort(p[2*i+1].begin(), p[2*i+1].end(), greater<Point>());
	}

	for (int i=1; i<1<<m; i++) {
		int s = -1;
		if (__builtin_popcount(i)%2 == 1) {
			s = 1;
		}
		int maxy = 0;
		for (int j=0; j<m; j++) {
			if (i&1<<j) {
				maxy = max(maxy, walls[j].y);
			}
		}
		int above = 0;
		for (const Point& it : points) {
			if (it.t == POINT && it.y > maxy) {
				above++;
			}
		}
		//cerr << nl << "SOLVE " << i << nl;
		memset(good, 0, sizeof good);
		for (int j=0; j<m; j++) {
			if (i&1<<j) {
				//cerr << "  SOLVE " << j << " left " << nl;
				solve(s, maxy, i, p[2*j]);
				//cerr << "  SOLVE " << j << " right" << nl;
				solve(s, maxy, i, p[2*j+1]);
			}
		}
		for (int k=0; k<q; k++) {
			if (good[k]) {
				ans[k] += s*above;
				//cerr << "upd " << k << " -> " << ans[k] << nl;
			}
		}
	}

	for (int i=0; i<q; i++) {
		cout << n-ans[i] << nl;
	}

	return 0;
}
