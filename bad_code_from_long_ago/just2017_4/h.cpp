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

	int n, m;
	string img[50];
	int border, interior;
	
	int T;
	cin >> T;
	while (T--) {
		cin >> n >> m;
		for (int i = 0; i < n; i++) {
			cin >> img[i];
		}
		border = 2*(n+m)-4;
		interior = 0;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (i == 0 || i == n-1 || j == 0 || j == m-1)
					border -= img[i][j]-'0';
				else 
					interior += img[i][j]-'0';
			}
		}
		if (interior >= border)
			cout << border << nl;
		else 
			cout << -1 << nl;
	}

	return 0;
}
