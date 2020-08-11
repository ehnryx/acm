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
const double EPS = 1e-10;

int main() {
	ios::sync_with_stdio(0); 
	cin.tie(0); cout.tie(0);
	
	int d, s;
	cin >> d >> s;
	double left, right, a;
	left = 1e-8; right = 1e8;
	while (right - left > EPS) {
		a = (left+right)/2;
		//cerr << "guess: " << a << " --> " << a*((exp(d/a/2)+exp(-d/a/2))/2 - 1) << nl;
		if (a*((exp(d/a/2)+exp(-d/a/2))/2 - 1) > s) {
//			if (a > d)
				left = a;
//			else
//				right = a;
		}
		else {
//			if (a > d)
				right = a;
//			else
//				left = a;
		}
	}
	//cerr << a << nl;
	cout << setprecision(10) << a*(exp(d/a/2) - exp(-d/a/2)) << nl;

	return 0;
}
