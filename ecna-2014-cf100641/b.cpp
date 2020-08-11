#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
const char nl = '\n';
const int N = 505;

string s;
int digs[N];
int len[N][N]; // len[l][k] = max i such that s[l..i] consists of repetitions of s[l..l+k-1]
int dp[N][N];

void prepareLen() {
	int n = s.size();
	for (int l = 0; l < n; l++) {
		for (int k = 1; l+k <= n; k++) {
			len[l][k] = l+k-1;
			for (int i = l + k; i + k - 1 < n; i += k) {
				for (int j = 0; j < k; j++) {
					if (s[i + j] != s[l + j]) {
						goto shit;
					}
				}
				len[l][k] += k;
			}
shit:;
		}
	}
}

int solve(int l, int r) {
	if (l == r) return 1;
	if (l > r) return 0;
	if (dp[l][r] != -1) return dp[l][r];
	int ans = 0x3f3f3f3f;
	for (int i = l; i < r; i++) {
		ans = min(ans, solve(l, i) + solve(i+1, r));
	}
	for (int k = 1; k < (r-l+1); k++) {
		if ((r-l+1)%k == 0 && len[l][k] >= r) {
			ans = min(ans, digs[(r-l+1)/k] + solve(l, l + k - 1) + (2 - 2*(k==1)));
		}
	}
	return dp[l][r] = ans;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	for (int i = 0; i < 10; i++) {
		digs[i] = 1;
	}
	for (int i = 10; i < 100; i++) {
		digs[i] = 2;
	}
	for (int i = 100; i < N; i++) {
		digs[i] = 3;
	}

	int tt = 1;
	while (cin >> s) {
		if (s == "0") break;
		memset(len, -1, sizeof len);
		memset(dp, -1, sizeof dp);
		prepareLen();
		cout << "Case " << tt++ << ": " << solve(0, s.size()-1) << endl;
	}

	return 0;
}
