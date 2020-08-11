#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-13;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

ld ncr[11][11];
ld power(ld x, int e) {
	ld res = 1;
	for (int i=0; i<e; i++) {
		res *= x;
	}
	return res;
}
ld prob(int r, int s, int x, int y) {
	ld res = 0;
	for (int i=x; i<=y; i++) {
		res += ncr[y][i]*power((ld)(s-r+1)/s,i)*power((ld)(r-1)/s,y-i);
	}
	return res;
}

//#define FILEIO
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);
#ifdef FILEIO
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#endif
	
	for (int i=0; i<11; i++) {
		ncr[i][0] = ncr[i][i] = 1;
		for (int j=1; j<i; j++) {
			ncr[i][j] = ncr[i-1][j] + ncr[i-1][j-1];
		}
	}

	int T;
	cin >> T;
	while (T--) {
		int r, s, x, y, w;
		cin >> r >> s >> x >> y >> w;
		ld p = prob(r,s,x,y);
		if (w*p > 1+EPS) cout << "yes" << nl;
		else cout << "no" << nl;
	}

	return 0;
}
