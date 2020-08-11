#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;
#define nl '\n'

inline void srand() { srand(clock() + time(nullptr)); }

template <class T, class U>
ostream& operator << (ostream& os, const pair<T,U>& v) {
	os << "(" << v.first << "," << v.second << ")"; return os;
}

template <class T>
ostream& operator << (ostream& os, const vector<T>& v) {
	for (const T& it : v) os << it << " "; return os;
}

template <class T>
ostream& operator << (ostream& os, const set<T>& v) {
	os << "{ "; for (const T& it : v) os << it << " "; os << "}"; return os;
}

template <class T, class U>
ostream& operator << (ostream& os, const map<T,U>& v) {
	os << "{ ";
	for (const pair<T,U>& it : v) os << "{" << it.first << "," << it.second << "} "; 
	os << "}"; return os;
}

template <class T>
inline T sqr(T x) { return x*x; }

const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
//const ld PI = M_PIl;
////////////////////////////////////////////////////////////////////////

const ll MOD = 1e9+7;
const ld EPS = 1e-9;

#define LOWER 0
#define UPPER 1

struct Point {
	ll x, dy;
	int type;
	Point() {}
	Point(ll x, ll dy, int t): x(x), dy(dy), type(t) {}
	bool operator < (const Point& other) const {
		return x < other.x;
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	int n, m;
	cin >> n >> m;	

	int lower[2*n+1], upper[2*m+1];
	for (int i = 0; i < 2*n+1; i++) {
		cin >> lower[i];
	}
	for (int i = 0; i < 2*m+1; i++) {
		cin >> upper[i];
	}

	vector<Point> points;
	for (int i = 0; i < n; i++) {
		points.push_back(Point(lower[2*i+1], lower[2*i+2] - lower[2*i], LOWER));
	}
	for (int i = 0; i < m; i++) {
		points.push_back(Point(upper[2*i+1], upper[2*i+2] - upper[2*i], UPPER));
	}
	sort(points.begin(), points.end());

	ll ans = 0;
	ll area = 0;
	ll region = 0;
	ll lb = lower[0];
	ll ub = upper[0];
	ll nlb, nub;
	ll prevx = -INF;
	bool open = false;
	for (const Point& cur : points) {
		nlb = lb;
		nub = ub;
		if (cur.type == LOWER) {
			nlb = lb + cur.dy;
		} else {
			nub = ub + cur.dy;
		}

		// upd region
		if (ub > lb && open) {
			region += (cur.x - prevx) * (ub - lb);
		}

		// close region
		if (nub < nlb && ub > lb) {
			area += region;
			if (region > 0) ans++;
			region = 0;
			open = false;
		}

		// open region
		if (nub > nlb && ub < lb) {
			open = true;
		}

		prevx = cur.x;
		lb = nlb;
		ub = nub;
	}

	cout << ans << " " << area << nl;

	return 0;
}
