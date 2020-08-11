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



int main() {
	freopen("popcorn.in", "r", stdin);
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	ll ncr[21][21];
	memset(ncr, 0, sizeof(ncr));
	for (int i = 0; i <= 20; i++) {
		ncr[i][i] = ncr[i][0] = 1;
		for (int j = 1; j < i; j++) {
			ncr[i][j] = ncr[i-1][j-1] + ncr[i-1][j];
		}
	}

	int n, m;
	int T;
	cin >> T;
	while (T--) {
		cin >> n >> m;
		cout << ncr[n][m] << nl;
	}

	return 0;
}
