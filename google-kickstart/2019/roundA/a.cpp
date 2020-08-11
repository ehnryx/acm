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

const int N = 1e5+1;
int s[N];

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

		int n, p;
		cin >> n >> p;
		for (int i=0; i<n; i++) {
			cin >> s[i];
		}
		sort(s, s+n);

		int cur = 0;
		for (int i=0; i<p; i++) {
			cur += s[p-1]-s[i];
		}
		int ans = cur;
		for (int i=p; i<n; i++) {
			cur += p*(s[i]-s[i-1]);
			cur -= s[i]-s[i-p];
			ans = min(ans, cur);
		}
		cout << ans << nl;

	}

	return 0;
}
