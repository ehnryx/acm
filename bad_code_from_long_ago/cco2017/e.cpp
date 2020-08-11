#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef complex<ld> pt;
typedef vector<pt> pol;
typedef pair<int,int> pii;
#define nl '\n'

const ll INF = 0x3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-9;

map<pii,int> dp_max;
map<pii,int> dp_min;

int solve_max(int n, int m) {
	pii cur(n,m);
	if (dp_max.count(cur)) {
		return dp_max[cur];
	}
	int res = 0;
	return dp_max[cur] = res;
}

int solve_min(int n, int m) {
	if (n*2 == m) {
		return 1;
	}
	pii cur(n,m);
	if (dp_min.count(cur)) {
		return dp_min[cur];
	}
	int res = INF;
	if (n*2 < m) {
		int mm = m - n*2;
		if (n > mm) swap(n, mm);
		res = 1 + solve_min(n, mm);
	}
	else {
		if (n % 2 == 0) {
			int nn = n;
			int mm = m - n/2;
			if (nn > mm) swap(nn, mm);
			res = min(res, 1 + solve_min(nn, mm));
		}
		if (m % 2 == 0) {
			int nn = n - m/2;
			int mm = m;
			if (nn > mm) swap(nn, mm);
			res = min(res, 1 + solve_min(nn, mm));
		}
	}
	return dp_min[cur] = res;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	int n, m;
	cin >> n >> m;

	if (n > m) swap(n, m);
	cout << solve_max(n, m) << " " << solve_min(n, m) << nl;

	return 0;
}
