#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef complex<ld> pt;
typedef vector<pt> pol;
#define nl '\n'

///* advent of code
typedef istringstream iss;
#define pb push_back
#define ins insert
#define multiset mset
#define getl(A) getline(cin, A)
//*/

const ll INF = 0x3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-9;

ll ncr[1001][1001];
ll ans[1001][1001];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	memset(ans, 0, sizeof(ans));
	memset(ncr, 0, sizeof(ncr));

	// precompute ncr
	for (int i = 0; i <= 1000; i++) {
		ncr[i][0] = ncr[i][i] = 1;
		for (int j = 1; j < i; j++) {
			ncr[i][j] = (ncr[i-1][j-1] + ncr[i-1][j]) % MOD;
		}
	}

	// precompute ans
	ans[0][0] = 1;
	for (int i = 1; i <= 1000; i++) {
		for (int j = 1; j <= 1000; j++) {
			ans[i][j] = j * ((ans[i-1][j-1] + ans[i-1][j]) % MOD) % MOD;
		}
	}

	// read input and solve
	freopen("galactic.in", "r", stdin);
	int n, k;
	int T;
	cin >> T;
	while (T--) {
		cin >> n >> k;
		if (k > n)
			cout << 0 << nl;
		else
			cout << ans[n][k] << nl;
	}

	return 0;
}
