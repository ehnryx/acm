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



//#define FILEIO
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);
#ifdef FILEIO
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#endif

	int k, n;
	cin >> k >> n;
	int val[k];
	for (int i=0; i<k; i++) {
		cin >> val[i];
	}

	int ans = -1;
	auto solve = [&] (ld len) {
		int tot = ans = 0;
		for (int i=0; i<k; i++) {
			ans += floor((val[i]-EPS)/len);
			tot += floor((val[i]+EPS)/len);
		}
		return tot >= n;
	};

	ld left = 0;
	ld right = INF;
	for (int r=0; r<100; r++) {
		ld mid = (left+right)/2;
		if (solve(mid)) {
			left = mid;
		} else {
			right = mid;
		}
	}

	if (!solve(left)) {
		assert(solve(left-EPS));
	}
	assert(ans != -1);
	cout << ans << nl;

	return 0;
}
