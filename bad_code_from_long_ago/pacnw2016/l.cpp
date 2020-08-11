#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

//#define DEBUG

#define ll long long
#define pii pair<int,int>
#define pdd pair<ldouble,ldouble>
#define ldouble long double
#define pt complex<ldouble>
#define ld double
#define nl '\n'
const ll MOD = 1e9+7;
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ldouble EPS = 1e-9;

struct Point {
	pt p;
	int id;
	Point(const pt& p, int i): p(p), id(i) {}
};

pt base;
double cp(const pt& a, const pt& b) { return imag(conj(a)*b); }
bool cmpout (const Point& a, const Point& b) {
	if (real(a.p) == real(b.p)) return imag(a.p) < imag(b.p);
	else return real(a.p) < real(b.p);
}
bool cmpleft (const Point& a, const Point& b) {
	return cp(a.p-base, b.p-base) > 0;
}
bool cmpright (const Point& a, const Point& b) {
	return cp(a.p-base, b.p-base) < 0;
}

int main() {
	ios::sync_with_stdio(0); 
	cin.tie(0); cout.tie(0);
	
	vector<Point> points;
	int x, y;
	string s;

	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> x >> y;
		points.push_back(Point(pt(x,y), i));
	}
	cin >> s;
	
	sort(points.begin(), points.end(), cmpout);
	for (int i = 0; i < n-2; i++) {
		base = points[i].p;
		if (s[i] == 'L') {
			sort(points.begin()+i+1, points.end(), cmpleft);
		}
		else {
			sort(points.begin()+i+1, points.end(), cmpright);
		}
	}

	for (int i = 0; i < n; i++) {
		cout << points[i].id+1 << " ";
	}
	cout << nl;

	return 0;
}
