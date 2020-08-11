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

int cnt[3][3];
ll nc3(ll n) {
	return n*(n-1)*(n-2)/6;
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

	int T;
	cin >> T;
	for (int tt=1; tt<=T; tt++) {
		cout << "Case #" << tt << ": ";

		int n, a, b, c, d, x, y, m;
		cin >> n >> a >> b >> c >> d >> x >> y >> m;
		memset(cnt, 0, sizeof cnt);
		for (int i=0; i<n; i++) {
			x = ((ll)a*x+b)%m;
			y = ((ll)c*y+d)%m;
			cnt[x%3][y%3]++;
		}

		ll ans = 0;
		for (int i=0; i<3; i++) {
			ll res1, res2;
			res1 = res2 = 1;
			for (int j=0; j<3; j++) {
				ans += nc3(cnt[i][j]);
				res1 *= cnt[i][j];
				res2 *= cnt[j][i];
			}
			ans += res1+res2;
		}
		cout << ans << nl;
	}

	return 0;
}
