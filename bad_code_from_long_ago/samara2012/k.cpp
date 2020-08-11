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

	string s;
	int need = 0;

	cin >> s;
	for (int i = 0; i < s.size(); i++) {
		if (s[i] == '(') {
			need++;
		}
		else {
			if (need == 0) {
				cout << "IMPOSSIBLE" << nl;
				return 0;
			}
			else {
				need--;
			}
		}
	}
	cout << s;
	for (int i = 0; i < need; i++) {
		cout << ")";
	} cout << nl;

	return 0;

}
