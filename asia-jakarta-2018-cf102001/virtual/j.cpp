#include <bits/stdc++.h>
using namespace std;

#define nl '\n'
typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
const int INF = 0x3f3f3f3f;

const int N = 15;
int dp[N+1][1<<N];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int n;
	cin >> n;

	int m[n+1];
	vector<string> s[n+1];
	m[0] = 1;
	s[0].push_back("");
	for (int i=1; i<=n; i++) {
		string t;
		cin >> t;
		m[i] = t.size();
		for (int bm=0; bm<1<<m[i]; bm++) {
			string cur;
			for (int j=0; j<m[i]; j++) {
				if (bm&1<<j) {
					cur.push_back(t[j]);
				}
			}
			s[i].push_back(cur);
		}
		sort(s[i].begin(), s[i].end());
		m[i] = 1<<m[i];
	}

	dp[0][0] = 0;
	for (int id=1; id<=n; id++) {
		dp[id][0] = -INF;
		int j = 0;
		for (int i=1; i<m[id]; i++) {
			while (j+1 < m[id-1] && s[id-1][j+1] < s[id][i]) {
				j++;
			}
			dp[id][i] = max(dp[id][i-1], dp[id-1][j] + (int)s[id][i].size());
		}
	}

	if (dp[n][m[n]-1] < 0) {
		cout << -1 << nl;
	} else {
		cout << dp[n][m[n]-1] << nl;
	}

	return 0;
}
