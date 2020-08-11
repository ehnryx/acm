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

struct Link {
	vector<int> points[4];
	Link(int a, int b, int c, int x, int y, int z) {
		points[0] = {a,b,c};
		points[2] = {x,y,z};
		if (a == x) {
			points[1] = {a,b,z};
			points[3] = {a,y,c};
		} else if (b == y) {
			points[1] = {a,b,z};
			points[3] = {x,b,c};
		} else {
			points[1] = {a,y,c};
			points[3] = {x,b,c};
		}
	}
	const vector<int>& operator [] (int i) const {
		return points[i];
	}
};

struct Square {
	int top, bottom, left, right;
	Square() {
		bottom = left = -INF;
		top = right = INF;
	}

	void add_link(const Link& link, int i) {
	}

	int in_range(const Link& link, int normal) {
		return 0;
	}
};

vector<Link> links[3];

Square bounding_square(int i) {
	Square bound;
	for (const Link& it : links[i]) {
		bound.add_link(it, i);
	}
	return bound;
}

bool connected(int i, int j) {
	Square bound = bounding_square(i);
	for (const Link& it : links[j]) {
		if (bound.in_range(it, i) != 1) return false;
	}
	return true;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);

	int T;
	cin >> T;
	while (T--) {
		int n;
		cin >> n;

		fill(links, links+3, vector<Link>());

		int a, b, c, x, y, z;
		for (int i = 0; i < n; i++) {
			cin >> a >> b >> c >> x >> y >> z;
			if (a == x) links[0].push_back(Link(a,b,c,x,y,z));
			else if (b == y) links[1].push_back(Link(a,b,c,x,y,z));
			else links[2].push_back(Link(a,b,c,x,y,z));
		}

		if (links[0].empty() + links[1].empty() + links[2].empty() >= 2) {
			cout << "NO" << nl;
			continue;
		}
		else if (links[0].empty()) {
			if (connected(1, 2)) cout << "YES" << nl;
			else cout << "NO" << nl;
		}
		else if (links[1].empty()) {
			if (connected(2, 0)) cout << "YES" << nl;
			else cout << "NO" << nl;
		}
		else if (links[2].empty()) {
			if (connected(0, 1)) cout << "YES" << nl;
			else cout << "NO" << nl;
		}
		else {
			if (connected(0, 1) + connected(1, 2) + connected(2, 0) >= 2) {
				cout << "YES" << nl;
			} else {
				cout << "NO" << nl;
			}
		}
	}

	return 0;
}
