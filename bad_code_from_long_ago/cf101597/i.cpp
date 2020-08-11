#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;
#define nl '\n'

///* advent of code
typedef istringstream iss;
#define pb push_back
#define ins insert
#define multiset mset
#define getl(A) getline(cin, A)
//*/

const ll INF = 0x3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-9;

ll base;
struct Point {
	int id;
	ll w, x;
	Point() {}
	Point(int id, ll w, ll x): id(id), w(w), x(x) {}
	operator int() { return id; }
	bool operator < (const Point& other) const {
		return abs(base - pull(1, base)) > abs(base - other.pull(1, base));
	}
	ld pull(ll ww, ll xx) const {
		return 1.L * (w*x + ww*xx) / (w + ww);
	}
};


int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	int a, b;
	cin >> a >> b;

	int n;
	cin >> n;

	ll weight, pos;
	weight = pos = 0;
	vector<Point> points;
	vector<int> bad;

	ll w, x;
	for (int i = 0; i < n; i++) {
		cin >> w >> x;
		if (x < a || x > b) {
			weight += w;
			pos += w*x;
			bad.push_back(i+1);
		} else {
			points.push_back(Point(i+1, w, x));
		}
	}

	if (weight == 0) {
		cout << n << nl;
		for (int i = 0; i < n; i++) {
			cout << 1 << " " << i+1 << nl;
		}
		return 0;
	}

	ld center = 1.L * pos/weight;

	if (center > b) {
		base = INF;
		sort(points.begin(), points.end());
		int id;
		for (id = 0; id < points.size() && 1.L * pos/weight > b; id++) {
			weight += points[id].w;
			pos += points[id].w * points[id].x;
			bad.push_back(points[id].id);
		}

		if (1.L * pos/weight > b) {
			cout << -1 << nl;
		} else {
			cout << n-bad.size() + 1 << nl;
			for (int i = id; i < points.size(); i++) {
				cout << 1 << " " << points[i] << nl;
			}
			cout << bad.size() << nl;
			for (int it : bad) cout << it << " "; cout << nl;
		}
	} 

	else if (center < a) {
		base = -INF;
		sort(points.begin(), points.end());
		int id;
		for (id = 0; id < points.size() && 1.L * pos/weight < a; id++) {
			weight += points[id].w;
			pos += points[id].w * points[id].x;
			bad.push_back(points[id].id);
		}

		if (1.L * pos/weight < a) {
			cout << -1 << nl;
		} else {
			cout << n-bad.size() + 1 << nl;
			for (int i = id; i < points.size(); i++) {
				cout << 1 << " " << points[i] << nl;
			}
			cout << bad.size() << nl;
			for (int it : bad) cout << it << " "; cout << nl;
		}
	} 

	else {
		cout << n-bad.size() + 1 << nl;
		for (int i = 0; i < points.size(); i++) {
			cout << 1 << " " << points[i] << nl;
		}
		cout << bad.size() << " ";
		for (int it : bad) cout << it << " "; cout << nl;
	}

	return 0;
}
