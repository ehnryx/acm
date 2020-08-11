#include <bits/stdc++.h>
using namespace std;

#define nl '\n'
typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
const int INF = 0x3f3f3f3f;

struct Point {
	ll n, d;
	int t;
	Point(ll a, ll b, int t): t(t) {
		ll g = abs(__gcd(a,b));
		n = a/g;
		d = b/g;
		if (d < 0) { d = -d; n = -n; }
		//cerr << "POINT " << n << "/" << d << " w/ " << t << endl;
	}
	bool operator < (const Point& o) const {
		if (d == 0 && o.d == 0) return n < o.n;
		if (n*o.d != d*o.n) return n*o.d < d*o.n;
		return t > o.t;
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int n;
	cin >> n;

	int x[n], y[n];
	for (int i=0; i<n; i++) {
		cin >> x[i] >> y[i];
	}

	for (int i=0; i<n; i++) {
		vector<Point> line;
		for (int j=1; j<n; j++) {
			if (j-1 == i || j == i) continue;
			int l = j;
			int r = j-1;
			if (x[l] > x[r]) swap(l,r);
			//cerr << " SEG " << x[l] << " " << y[l] << " -> " << x[r] << " " << y[r] << nl;
			if (x[l] == x[i] && x[r] == x[i]) {
			} else if (x[l] == x[i]) {
				if (y[l] > y[i]) {
					line.push_back(Point(1, 0, -1));
					line.push_back(Point(y[r]-y[i], x[r]-x[i], 1));
				} else {
					line.push_back(Point(-1, 0, 1));
					line.push_back(Point(y[r]-y[i], x[r]-x[i], -1));
				}
			} else if (x[r] == x[i]) {
				if (y[r] > y[i]) {
					line.push_back(Point(-1, 0, 1));
					line.push_back(Point(y[l]-y[i], x[l]-x[i], -1));
				} else {
					line.push_back(Point(1, 0, -1));
					line.push_back(Point(y[l]-y[i], x[l]-x[i], 1));
				}
			} else if (x[l] < x[i] && x[i] < x[r]) {
				line.push_back(Point(-1, 0, 1));
				line.push_back(Point(1, 0, -1));
				if ((ll)(x[l]-x[r])*(y[i]-y[l]) > (ll)(x[i]-x[l])*(y[l]-y[r])) {
					line.push_back(Point(y[l]-y[i], x[l]-x[i], -1));
					line.push_back(Point(y[r]-y[i], x[r]-x[i], 1));
				} else {
					line.push_back(Point(y[l]-y[i], x[l]-x[i], 1));
					line.push_back(Point(y[r]-y[i], x[r]-x[i], -1));
				}
			} else { // same side
				Point s(y[l]-y[i], x[l]-x[i], 1);
				Point t(y[r]-y[i], x[r]-x[i], -1);
				if (t < s) { swap(s.t, t.t); }
				line.push_back(s);
				line.push_back(t);
			}
		}

		sort(line.begin(), line.end());
		//cerr << nl;
		//cerr << " @ " << i << " : " << x[i] << " " << y[i] << endl; for (const Point& it : line) {
			//cerr << it.n << "/" << it.d << " -> " << it.t << nl; }
		//cerr << nl;
		if (line.empty()) continue;
		if (line.front().n == -1 && line.front().d == 0 && line.back().n == 1 && line.back().d == 0) {
			bool ok = false;
			int cnt = line.front().t;
			for (int j=1; j<line.size(); j++) {
				if (cnt < 1) {
					//cerr << "BREAK @ " << line[j].n << "/" << line[j].t << " w/ " << cnt << endl;
					ok = true;
					break;
				}
				cnt += line[j].t;
			}
			if (!ok) {
				cout << "Impossible" << nl;
				return 0 ;
			}
		}
	}

	cout << "Possible" << nl;

	return 0;
}
