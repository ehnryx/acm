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



#define FILEIO
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);
#ifdef FILEIO
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif

	int n, m, k;
	cin >> n >> m;

	int fail[m+1]; memset(fail, 0, sizeof fail);
	for (int i=0; i<n; i++) {
		cin >> k;
		for (int j=0; j<k; j++) {
			int a;
			cin >> a;
			fail[a] |= 1<<i;
		}
	}

	int ans = (1<<21) - 1;
	for (int bm = 0; bm < 1<<n; bm++) {
		bool good = true;
		for (int i=1; i<=m; i++) {
			if (!(bm & fail[i])) {
				good = false;
				break;
			}
		}
		if (good && __builtin_popcount(bm) < __builtin_popcount(ans)) {
			ans = bm;
		}
	}

	cout << __builtin_popcount(ans) << nl;
	for (int i=0; i<n; i++) {
		if (ans & 1<<i) cout << i+1 << " ";
	}
	cout << nl;

	return 0;
}
