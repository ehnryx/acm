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
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int N = 3e5+1;
int dp[N];

void init() {
	memset(dp, INF, sizeof dp);
}

int solve(int n, int a[]) {
	if (n == 0) return 0;
	if (n == 1) return -1;
	if (dp[n] != INF) return dp[n];

	int car = -1;
	int trailer = -1;

	if (a[n] - a[n-1] < 2000 && a[n-1] - a[n-2] > 1000) {
		car = solve(n-2, a);
		if (car >= 0) car++;
	}

	if (n > 2 && a[n] - a[n-1] < 2000 && a[n-1] - a[n-2] < 2000 && a[n-2] - a[n-3] > 1000) {
		trailer = solve(n-3, a);
		if (trailer >= 0) trailer++;
	}

	if (car == -2 || trailer == -2) return dp[n] = -2;
	if (car < 0) return dp[n] = trailer;
	if (trailer < 0) return dp[n] = car;
	if (car == trailer) return dp[n] = car;
	return dp[n] = -2;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);
	init();

	int n;
	cin >> n;

	int a[n+1];
	a[0] = -INF;
	for (int i=1; i<=n; i++) {
		cin >> a[i];
	}

	int res = solve(n, a);
	if (res == -1) {
		cout << "Impossible" << nl;
	} else if (res == -2) {
		cout << "Ambiguous" << nl;
	} else {
		int trailers = n - 2*res;
		int cars = res - trailers;
		cout << "Cars without trailers: " << cars << nl;
		cout << "Cars with trailers: " << trailers << nl;
	}

	return 0;
}
