#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#define TESTFILE "zeriba"

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



void solve() {
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);
#ifdef ONLINE_JUDGE
	freopen(TESTFILE ".in", "r", stdin);
#endif

	int T;
	cin >> T;

	for (int tt=1; tt<=T; tt++) {
		cout << "Case " << tt << ": ";
		solve();
	}

	return 0;
}
