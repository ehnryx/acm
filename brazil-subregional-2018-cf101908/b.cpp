#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
using namespace std;

#define nl '\n'

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
const int INF = 0x3f3f3f3f;
const int B = 105;

int dp[B][B];

int solve(int x, int y) {
	if (x == 0 || y == 0 || x == y) return 3*B-1;
	if (dp[x][y] != -1) return dp[x][y];
	bitset<3*B> a; int mex = 0;
	for (int i = 0; i < x; i++) {
		a[solve(i, y)] = 1;
	}
	for (int i = 0; i < y; i++) {
		a[solve(x, i)] = 1;
	}
	for (int u = 1; u <= min(x, y); u++) {
		a[solve(x-u, y-u)] = 1;
	}
	while (a[mex]) mex++;
	return dp[x][y] = mex;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	memset(dp, -1, sizeof dp);
	/*
	for (int i = 0; i < 40; i++) {
		for (int j = 0; j < 40; j++) {
			if (solve(i, j)) cout << 1;
			else cout << 0;
		}
		cout << nl;
	} return 0;
	*/

	int n; cin >> n;
	int ans = 0;
	bool shit = 0;
	for (int i = 0; i < n; i++) {
		int l, c; cin >> l >> c;
		if (solve(l, c) == 3*B-1) {
			shit = 1;
		} else ans ^= solve(l, c);
		//if (solve(l, c)) cerr << "win " << i << nl, ans = !ans;
	}
	puts(ans || shit ? "Y" : "N");

	return 0;
}
