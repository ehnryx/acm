#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

//#define DEBUG
//#define USE_MAGIC_IO

#define ll long long
#define pii pair<int,int>
#define pdd pair<double,double>
#define ldouble long double
#define nl '\n'
const ll MOD = 1e9+7;
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;

struct BIT {
	int size;
	vector<int> freq;
	void resize(int n) {
		freq.resize(n+1);
		memset(&freq[0], 0, (n+1)*sizeof(freq[0]));
		size = n;
	}
	void update(int x, int cnt) {
		for ( ; x <= size; x += x & -x) 
			freq[x] += cnt;
	}
	void insert(int xl, int xr, int cnt=1) {
		update(xl, cnt);
		update(xr+1, -cnt);
	}
	int query(int x) {
		int sum = 0;
		for ( ; x > 0; x -= x & -x)
			sum += freq[x];
		return sum;
	}
};

struct LineSweep {
	struct Point {
		int id; // INF for start, -1 for end, 0 to n otherwise
		int x; // position to sort by
		int start, end; // for rectangles, should be mapped
		Point(int id, int x, int start, int end) {
			this->id = id;
			this->x = x;
			this->start = start;
			this->end = end;
		}
		bool operator < (const Point& other) const {
			if (x == other.x) return id < other.id;
			else return x < other.x;
		}
	};
	set<int> ycompress;
	map<int,int> mapped;
	vector<Point> line;
	BIT segments;
	void insert_point(int id, int x, int y) {
		line.push_back(Point(id, x, y, y));
		ycompress.insert(y);
	}
	void insert_rect(int xbl, int ybl, int xtr, int ytr) {
		line.push_back(Point(INF, xbl, ybl, ytr));
		line.push_back(Point(-1, xtr, ybl, ytr));
		ycompress.insert(ybl);
		ycompress.insert(ytr);
	}
	void compress() {
		int curr = 2;
		for (int y: ycompress) {
			mapped.insert(pair<int,int>(y, curr++));
		}
		segments.resize(curr+1);
	}
	void sweep(int ans[]) {
		sort(line.begin(), line.end());
		for (Point p: line) {
			if (p.id == -1) {
				// remove segment
				segments.insert(mapped[p.start], mapped[p.end], -1);
			}
			else if (p.id == INF) {
				// add segment
				segments.insert(mapped[p.start], mapped[p.end], 1);
			}
			else {
				// query
				ans[p.id] = segments.query(mapped[p.start]);
			}
		}
	}
};

int main() {
	ios::sync_with_stdio(0); 
	cin.tie(0); cout.tie(0);

	LineSweep mess;
	int n, m, x, y, a, b;
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		cin >> a >> b;
		mess.insert_point(i, a, b);
	}
	for (int i = 0; i < m; i++) {
		cin >> a >> b >> x >> y;
		mess.insert_rect(a, b, x, y);
	}
	mess.compress();

	int ans[n];
	mess.sweep(ans);
	for (int i = 0; i < n; i++)
		cout << ans[i] << nl;

	return 0;
}
