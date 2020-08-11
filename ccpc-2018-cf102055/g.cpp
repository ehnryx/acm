#include <bits/stdc++.h>
using namespace std;

#define nl '\n'
typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;

const int INF = 0x3f3f3f3f;
const int N = 1e5+10;
const int M = 1e9+7;

ll fac[N], facinv[N];

ll inv(ll x) {
	ll ans = 1, cur = x, e = M-2;
	while (e) {
		if (e%2) ans *= cur, ans %= M;
		cur *= cur, cur %= M;
		e /= 2;
	}
	return ans;
}

void pre() {
	fac[0] = facinv[0] = 1;
	for (int i = 1; i < N; i++) {
		fac[i] = fac[i-1] * i % M;
		facinv[i] = inv(fac[i]);
	}
}

ll choose(int n, int k) {
	if (k > n || k < 0) return 0;
	return fac[n] * facinv[n-k] % M * facinv[k] % M;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	pre();
	int T; cin >> T;
	for (int tt = 1; tt <= T; tt++) {
		cout << "Case " << tt << ": ";
		int n, m; cin >> n >> m;
		cout << choose(n+1, 4) * choose(m+1, 4) % M << nl;
	}

	return 0;
}
