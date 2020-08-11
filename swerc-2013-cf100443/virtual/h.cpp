#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;

#define nl '\n'

const ll MOD = 21092013;

const int N = 1e5+1;
int suff[N], nxtl[N], nxtr[N];
ll memo[N];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int T;
	cin >> T;
	for (int ts=1; ts<=T; ts++) {
		string s, t;
		cin >> s >> t;

		vector<char> path;
		for (char c : s) {
			if (c == 'U') {
				if (!path.empty()) path.pop_back();
			} else {
				path.push_back(c);
			}
		}

		int n = t.size();
		suff[n] = 0;
		int lastl = nxtl[n] = n;
		int lastr = nxtr[n] = n;
		for (int i=n-1; i>=0; i--) {
			if (t[i] != 'U') suff[i] = suff[i+1]+1;
			else suff[i] = suff[i+1];
			if (t[i] == 'L') lastl = i;
			if (t[i] == 'R') lastr = i;
			nxtl[i] = lastl;
			nxtr[i] = lastr;
		}

		// memo[i] = number of subsequences starting at j with j>=i
		memset(memo, 0, sizeof memo);
		memo[n] = 0;
		for (int i = n-1; i >= 0; i--) {
			memo[i] = (memo[nxtl[i+1]] + memo[nxtr[i+1]] + 1) % MOD;
		}
		ll memolast = (memo[nxtl[0]] + memo[nxtr[0]] + 1) % MOD;

		ll ans = memolast;
		//cerr << "memolast: " << memolast << nl;
		for (int i=0; i<n && !path.empty(); i++) {
			if (t[i] == 'U') {
				if (path.back() == 'L') {
					if (nxtr[i] == n) ans++;
					else ans += memo[nxtr[i]] + 1;
				}
				else {
					if (nxtl[i] == n) ans++;
					else ans += memo[nxtl[i]] + 1;
				}
				path.pop_back();
			}
		}

		cout << "Case " << ts << ": " << ans % MOD << nl;
	}

	return 0;
}
