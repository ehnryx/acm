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

int main() {
	ios::sync_with_stdio(0); 
	cin.tie(0); cout.tie(0);

	unordered_map<int,unordered_set<int>> x;
	unordered_map<int,unordered_set<int>> y;

	int n, a, b;
	cin >> n;
	vector<pair<int,int>> sad;
	for (int i = 0; i < n; i++) {
		cin >> a >> b;
		x[a].insert(b);
		y[b].insert(a);
	}

	ll ans = 0;
	for (pair<int,unordered_set<int>> pt : x) {
		//cerr << "x: " << pt.first << endl;
		if (x.count(pt.first+2018))
			for (int xv : pt.second)
				ans += x[pt.first+2018].count(xv);
		if (x.count(pt.first+1118))
			for (int xv : pt.second) 
				ans += x[pt.first+1118].count(xv+1680)
						+ x[pt.first+1118].count(xv-1680);
	}
	for (pair<int,unordered_set<int>> pt : y) {
		//cerr << "y: " << pt.first << endl;
		if (y.count(pt.first+2018))
			for (int yv : pt.second)
				ans += y[pt.first+2018].count(yv);
		if (y.count(pt.first+1118))
			for (int yv : pt.second) 
				ans += y[pt.first+1118].count(yv+1680)
						+ y[pt.first+1118].count(yv-1680);
	}
	cout << ans << nl;

	return 0;
}
