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

ll nc2(int n) {
	return (ll)n*(n-1)/2;
}

const int N = 26;
int cnt[N];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);

	int T;
	cin >> T;
	while (T--) {
		int n, k;
		cin >> n >> k;

		memset(cnt, 0, sizeof cnt);
		char c;
		for (int i=0; i<n; i++) {
			cin >> c;
			cnt[c-'a']++;
		}

		ll ans = 0;
		for (int j = 'a'; j <= 'z'; j++) {
			ll cur = 0;

			ans = max(ans, cur);
		}

		cout << ans << nl;
	}

	return 0;
}
