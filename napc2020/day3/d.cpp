#include <bits/stdc++.h>
using namespace std;

#define nl '\n'
typedef long long ll;
typedef long double ld;
const ll MOD = 1e9 + 7;

ll power(ll n, int e, ll m) {
	ll r = 1;
	for(;e>0;e/=2) {
		if(e&1) r = r*n % m;
		n = n*n % m;
	}
	return r;
}

const int N = 3e5 + 1;
int p[N], dp[N], sum[N];

int main() {
	ios::sync_with_stdio(0); cin.tie(0);

	int n, m;
	cin >> n >> m;
	string s;
	cin >> s;
	for(int i=1; i<=n; i++) {
		p[i] = (p[i-1] * 10 + s[i-1] - '0') % m;
	}

	dp[0] = sum[0] = 1;
	for(int i=1; i<=n; i++) {
		if(p[i] == 0) {
			int len = min(i, 9);
			for(int k=1; k<=len; k++) {
				int v = stoi(s.substr(i-k, k));
				bool ok = true;
				for(int mod=m; mod%2 == 0; mod/=2) {
					ok &= (v%2 == 0);
					v /= 2;
				}
				for(int mod=m; mod%5 == 0; mod/=5) {
					ok &= (v%5 == 0);
					v /= 5;
				}
				if(ok) {
					dp[i] = sum[i-k];
					break;
				}
			}
		}
		sum[i] = (dp[i] + sum[i-1]) % MOD;
	}
	cout << dp[n] << nl;

	return 0;
}
