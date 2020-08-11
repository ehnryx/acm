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

struct Point {
	ll x, y;
};

ll sqrdist(const Point& a, const Point& b) {
	return (a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y);
}
ldouble cosangle(const Point& a, const Point& b, const Point& c) {
	return 1.0 * (sqrdist(a,b) + sqrdist(b,c) - sqrdist(c,a)) / (2*sqrt(sqrdist(a,b))*sqrt(sqrdist(b,c)));
}
ll area(const Point& a, const Point& b, const Point& c) {
	return (a.x*b.y + b.x*c.y + c.x*a.y) - (a.y*b.x + b.y*c.x + c.y*a.x);
}

int main() {
	ios::sync_with_stdio(0); 
	cin.tie(0); cout.tie(0);
	
	bool good = true;
	int n, m;
	cin >> n >> m;
	Point one[n];
	Point two[m];
	for (int i = 0; i < n; i++) {
		cin >> one[i].x >> one[i].y;
	}
	for (int i = 0; i < m; i++) {
		cin >> two[i].x >> two[i].y;
	}

	int other = 0;
	int best = 0;
	for (other = 0; other < m; other++) {
		//cerr << cosangle(one[n-1], one[0], two[other]) << " " << cosangle(one[n-1], one[0], two[best]) << nl;
		if (cosangle(one[n-1], one[0], two[other]) < cosangle(one[n-1], one[0], two[best]))
			best = other;
	}
	other = best;
	//cerr << "best: " << best << nl;
	for (int curr = 0; curr < n; curr++) {
		// check signed area
		//cerr << "area: " << area(one[curr], one[(curr+1)%n], two[other]) << nl;
		if (area(one[curr], one[(curr+1)%n], two[other]) >= 0) {
			good = false;
			break;
		}
		// find next point
		while (cosangle(one[(curr+n-1)%n], one[curr], two[other]) > cosangle(one[(curr+n-1)%n], one[curr], two[(other+1)%m])) {
			other = (other+1)%m;
			if (area(one[curr], one[(curr+1)%n], two[other]) >= 0) {
				good = false;
				break;
			}
		}
		//cerr << "final: " << "curr: " << curr << " other: " << other << nl;
		if (!good) break;
	}

	if (!good) {
		//cerr << "NEXT" << nl;
		good = true;
		other = 0;
		best = 0;
		for (other = 0; other < n; other++) {
			if (cosangle(one[m-1], one[0], two[other]) < cosangle(one[m-1], one[0], two[best]))
				best = other;
		}
		other = best;
		for (int curr = 0; curr < m; curr++) {
			// check signed area
			//cerr << "area: " << area(two[curr], two[(curr+1)%m], one[other]) << nl;
			if (area(two[curr], two[(curr+1)%m], one[other]) >= 0) {
				good = false;
				break;
			}
			// find next point
			while (cosangle(two[(curr+m-1)%m], two[curr], one[other]) > cosangle(two[(curr+m-1)%m], two[curr], one[(other+1)%n])) {
				other = (other+1)%n;
				if (area(two[curr], two[(curr+1)%m], one[other]) >= 0) {
					good = false;
					break;
				}
			}
			//cerr << "final: " << "curr: " << curr << " other: " << other << nl;
			if (!good) break;
		}
	}
	if (good)
		cout << "YES" << nl;
	else 
		cout << "NO" << nl;

	return 0;
}
