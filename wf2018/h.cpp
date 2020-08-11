#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

pt center;

struct Point {
	int id;
	pii v;
	ld ang;
	Point() {}
	Point(int i, const pii& v): id(i), v(v) {
		ang = arg(pt(v.first, v.second) - center);
	}
	bool operator < (const Point& p) const { 
		return ang < p.ang || (ang == p.ang && id < p.id); 
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);

	int n, w, h;
	cin >> n >> w >> h;
	center = pt((ld)w/2, (ld)h/2);

	vector<Point> p;
	int a, b, x, y;
	for (int i = 0; i < n; i++) {
		cin >> a >> b >> x >> y;
		p.push_back(Point(i, pii(a,b)));
		p.push_back(Point(i, pii(x,y)));
	}
	sort(p.begin(), p.end());

	unordered_set<int> cur;
	int front = 0;
	int back = 0;
	while (back < 2*n) {
		while (!cur.count(p[front].id)) {
			cur.insert(p[front].id);
			front = (front+1 == 2*n ? 0 : front+1);
		}
		if (cur.size() == n) {
			break;
		}

		do {
			cur.erase(p[back++].id);
		} while (back < 2*n && p[back-1].id != p[front].id);
		if (back == 2*n) break;
	}

	if (back == 2*n) {
		cout << 2 << nl;
		cout << 0 << " " << 0.5 << " " << w << " " << h-0.5 << nl;
		cout << 0 << " " << h-0.5 << " " << w << " " << 0.5 << nl;
	}
	else {
		pair<ld,ld> left = p[back].v;
		pair<ld,ld> right = p[front].v;
		if (left.first == 0) left.second += 0.5;
		else if (left.first == w) left.second -= 0.5;
		else if (left.second == 0) left.first -= 0.5;
		else left.first += 0.5;
		if (right.first == 0) right.second += 0.5;
		else if (right.first == w) right.second -= 0.5;
		else if (right.second == 0) right.first -= 0.5;
		else right.first += 0.5;

		cout << 1 << nl;
		cout << left.first << " " << left.second << " " << right.first << " " << right.second << nl;
	}

	return 0;
}
