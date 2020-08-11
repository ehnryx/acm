#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

//#define DEBUG

#define ll long long
#define pii pair<int,int>
#define pdd pair<ldouble,ldouble>
#define ldouble long double
#define pt complex<ldouble>
#define ld ldouble
#define nl '\n'
const ll MOD = 1e9+7;
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ldouble EPS = 1e-9;

int main() {
	ios::sync_with_stdio(0); 
	cin.tie(0); cout.tie(0);

	int n, k, r; cin >> n >> k >> r;
	vector<bool> c(n);
	for (int i = 0; i < k; i++) {
		int j; cin >> j; c[j-1] = 1;
	}
	int num = 0;
	for (int i = 0; i < r; i++) {
		num += c[i];
	}
	int ans = 0;
	if (num == 0) {
		num = 2;
		ans = 2;
		c[r-1] = 1;
		c[r-2] = 1;
	} else if (num == 1) {
		num = 2;
		ans = 1;
		if (c[r-1])
			c[r-2] = 1;
		else c[r-1] = 1;
	}
	for (int i = r; i < n; i++) {
//		cout << num << endl;
		if (c[i - r])
			num--;
		if (c[i])
			num++;
		if (num < 2) {
			ans++;
			num++;
			c[i] = 1;
		}
	}
	cout << ans << endl;

	return 0;
}
