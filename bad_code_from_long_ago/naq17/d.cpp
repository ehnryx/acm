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
const double EPS = 1e-5;

struct Point {
	int x, y;
	int s;
	double dist(const Point& other) {
		return sqrt((x-other.x)*(x-other.x) + (y-other.y)*(y-other.y));
	}
};

double getveloce(double m, Point pt[], const vector<int>& perm) {
	int n = perm.size();
	double left, right, v;
	left = 1e-6; right = 1e18;
	while (right-left > EPS) {
		v = (left+right)/2;
		//cerr << v << nl;
		double t = (pt[n].dist(pt[perm[0]])) / (v);
		for (int i = 1; i < n; i++) {
			if (t > pt[i-1].s)
				goto bad;
			v *= m;
			t += (pt[perm[i]].dist(pt[perm[i-1]])) / (v);
		}
		if (t > pt[n-1].s) {
			bad:
			left = (left+right)/2;
		} else {
			right = (left+right)/2;
		}
	}
	return (left+right)/2;
}

int main() {
	ios::sync_with_stdio(0); 
	cin.tie(0); cout.tie(0);
	
	int n;
	cin >> n;
	Point pt[n+1];
	pt[n].x = pt[n].y = 0;
	vector<int> perm;
	for (int i = 0; i < n; i++) {
		perm.push_back(i);
		cin >> pt[i].x >> pt[i].y >> pt[i].s;
	}
	double m;
	cin >> m;

	double optv = INFLL;
	do {
		optv = min(optv, getveloce(m, pt, perm));
	} while (next_permutation(perm.begin(), perm.end()));

	cout << setprecision(10) << optv << nl;

	return 0;
}
