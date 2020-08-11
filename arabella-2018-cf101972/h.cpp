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

	set<int> valid[26];
	int cnt[26];

	int T;
	cin >> T;
	while (T--) {
		int n, m, k;
		cin >> n >> m >> k;
		string s, t;
		cin >> s >> t;

		fill(valid, valid+26, set<int>());
		for (int i=k-1; i<n; i++) {
			valid[s[i]-'a'].insert(s[i-k+1]-'a');
		}

		ll ans = 0;
		memset(cnt, 0, sizeof cnt);
		for (int i=0; i<m; i++) {
			cnt[t[i]-'a']++;
			for (int it : valid[t[i]-'a']) {
				ans += cnt[it];
			}
		}
		cout << ans << nl;
	}

	return 0;
}
