#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#pragma GCC optimize("O3")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

// MAGIC IO
inline char get(void) {
	static char buf[100000], *S = buf, *T = buf;
	if (S == T) {
		T = (S = buf) + fread(buf, 1, 100000, stdin);
		if (S == T) return EOF;
	}
	return *S++;
}
inline void read(int &x) {
	static char c; x = 0; int sgn = 0;
	for (c = get(); c < '0' || c > '9'; c = get()) if (c == '-') sgn = 1;
	for (; c >= '0' && c <= '9'; c = get()) x = x * 10 + c - '0';
	if (sgn) x = -x;
}
void readchar(char& c) {
	while (isspace(c = get()));
}
// END MAGIC IO

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

#define POINT 0
#define WALL 1
#define QUERY 2

int bx, by;
struct Point {
	int x, y;
	int t, d;
	bool operator < (const Point& o) const {
		ll ltop = x-bx; ll lbot = y-by;
		ll rtop = o.x-bx; ll rbot = o.y-by;
		if (lbot < 0) { lbot = -lbot; ltop = -ltop; }
		if (rbot < 0) { rbot = -rbot; rtop = -rtop; }
		return ltop*rbot < lbot*rtop;
	}
	bool operator > (const Point& o) const {
		ll ltop = x-bx; ll lbot = y-by;
		ll rtop = o.x-bx; ll rbot = o.y-by;
		if (lbot < 0) { lbot = -lbot; ltop = -ltop; }
		if (rbot < 0) { rbot = -rbot; rtop = -rtop; }
		return ltop*rbot > lbot*rtop;
	}
	bool operator == (const Point& o) const {
		ll ltop = x-bx; ll lbot = y-by;
		ll rtop = o.x-bx; ll rbot = o.y-by;
		if (lbot < 0) { lbot = -lbot; ltop = -ltop; }
		if (rbot < 0) { rbot = -rbot; rtop = -rtop; }
		return ltop*rbot == lbot*rtop;
	}
};

struct Wall {
	int a, b, y;
};

const int N = 4e4+1;
int ans[N], good[N];
int line[2*N+17];

void solve(int s, int bm, int maxv, const vector<Point>& p) {
	int goal = __builtin_popcount(bm)-1;
	Point cur{bx+1, by};
	int pos = 0;
	int active = 0;
	int cnt = 0;
	int n = p.size();
	for (int i=0; i<n; i++) {
		const auto& it = p[i];
		if (it == cur) {
			// add to line
			line[pos++] = i;
		} else {
			// deal with line
			bool skip = false;
			vector<int> queries, remove;
			int add = 0;
			for (int j=0; j<pos; j++) {
				const auto& jt = p[line[j]];
				if (jt.t == WALL) {
					if (!(1<<jt.d&bm)) continue;
					// upd skip when adding wall
					skip |= (jt.y > by && !(active&1<<jt.d));
					// upd wall
					if (active&1<<jt.d) {
						remove.push_back(jt.d);
					} else {
						active |= 1<<jt.d;
					}
				} else if (jt.t == POINT) {
					add += (jt.y > maxv);
				} else { // jt.t == QUERY
					queries.push_back(jt.d);
				}
			}
			if (!skip && __builtin_popcount(active) == goal) {
				// update queries
				for (int jt : queries) {
					ans[jt] -= s*cnt;
					good[jt] = true;
				}
			}
			cnt += add;
			for (int jt : remove) {
				active &= ~(1<<jt);
			}
			// reset the line
			pos = 0;
			line[pos++] = i;
			cur = it;
		}
	}
	{ // if there is a line left over
		bool skip = false;
		vector<int> queries, remove;
		int add = 0;
		for (int j=0; j<pos; j++) {
			const auto& jt = p[line[j]];
			if (jt.t == WALL) {
				if (!(1<<jt.d&bm)) continue;
				// upd skip when adding wall
				skip |= (jt.y > by && !(active&1<<jt.d));
				// upd wall
				if (active&1<<jt.d) {
					remove.push_back(jt.d);
				} else {
					active |= 1<<jt.d;
				}
			} else if (jt.t == POINT) {
				add += (jt.y > maxv);
			} else { // jt.t == QUERY
				queries.push_back(jt.d);
			}
		}
		if (!skip && __builtin_popcount(active) == goal) {
			// update queries
			for (int jt : queries) {
				ans[jt] -= s*cnt;
				good[jt] = true;
			}
		}
	}
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

	int n, m, q;
	//cin >> n >> m >> q;
	read(n); read(m); read(q);

	vector<Point> points, queries;
	vector<Wall> walls;
	for (int i=0; i<n; i++) {
		int x, y;
		//cin >> x >> y;
		read(x); read(y);
		points.push_back({x,y,POINT});
	}
	for (int i=0; i<m; i++) {
		int a, b, y;
		//cin >> a >> b >> y;
		read(a); read(b); read(y);
		walls.push_back({a,b,y});
	}
	for (int i=0; i<q; i++) {
		int x, y;
		//cin >> x >> y;
		read(x); read(y);
		queries.push_back({x,y,QUERY,i});
	}

	vector<Point> p[10];
	map<int,int> above;
	for (int i=0; i<m; i++) {
		p[2*i] = p[2*i+1] = queries;
		for (const Point& it : points) {
			if (it.y > walls[i].y) {
				p[2*i].push_back(it);
				p[2*i+1].push_back(it);
			}
		}
		for (int j=0; j<m; j++) {
			const auto& it = walls[j];
			if (it.y != walls[i].y) {
				p[2*i].push_back({it.a,it.y,WALL,j});
				p[2*i].push_back({it.b,it.y,WALL,j});
				p[2*i+1].push_back({it.a,it.y,WALL,j});
				p[2*i+1].push_back({it.b,it.y,WALL,j});
			}
		}
		tie(bx,by) = {walls[i].a, walls[i].y};
		sort(p[2*i].begin(), p[2*i].end());
		tie(bx,by) = {walls[i].b, walls[i].y};
		sort(p[2*i+1].begin(), p[2*i+1].end(), greater<Point>());

		if (!above.count(walls[i].y)) {
			for (const Point& it : points) {
				above[walls[i].y] += (it.y > walls[i].y);
			}
		}
	}

	for (int bm=1; bm<1<<m; bm++) {
		int maxv = 0;
		for (int j=0; j<m; j++) {
			if (bm&1<<j) {
				maxv = max(maxv, walls[j].y);
			}
		}
		int s = (__builtin_popcount(bm)%2 == 1 ? 1 : -1);
		memset(good, 0, sizeof good);
		for (int j=0; j<m; j++) {
			if (bm&1<<j) {
				tie(bx,by) = {walls[j].a, walls[j].y};
				solve(s, bm, maxv, p[2*j]);
				tie(bx,by) = {walls[j].b, walls[j].y};
				solve(s, bm, maxv, p[2*j+1]);
			}
		}
		for (int i=0; i<q; i++) {
			if (good[i]) {
				//assert(above.count(maxv));
				ans[i] += s*above[maxv];
			}
		}
	}

	for (int i=0; i<q; i++) {
		//cout << n-ans[i] << nl;
		printf("%d\n", n-ans[i]);
	}

	return 0;
}
