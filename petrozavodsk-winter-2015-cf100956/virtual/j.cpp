#include <bits/stdc++.h>
using namespace std;

#define nl '\n'
typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
const int INF = 0x3f3f3f3f;
const int MOD = 1e9+7;

const int N = 2e3+1;
int a[N];
ll ncr[N][N];
ll dp[N][N];
ll cnt[N], fun[N];

struct BIT {
	vector<ll> bit = vector<ll>(N,0);
	void insert(int x, ll v) {
		for ( ; x<N; x+=x&-x) {
			bit[x] = (bit[x]+v) % MOD;
		}
	}
	ll query(int x) {
		ll res = 0;
		for ( ; x>0; x-=x&-x) {
			res = (res+bit[x]) % MOD;
		}
		return res;
	}
	ll query(int l, int r) {
		return (query(r)-query(l-1)) % MOD;
	}
} bit[N];

ll power(ll b, int e) {
	ll res = 1;
	while (e>0) {
		if (e&1) res = res*b % MOD;
		b = b*b % MOD;
		e/=2;
	}
	return res;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	for (int i=0; i<N; i++) {
		ncr[i][0] = ncr[i][i] = 1;
		for (int j=1; j<i; j++) {
			ncr[i][j] = (ncr[i-1][j-1] + ncr[i-1][j]) % MOD;
		}
	}

	int n;
	cin >> n;

	for (int i=1; i<=n; i++) {
		fun[i] = power(i,n);
		for (int j=1; j<i; j++) {
			ll cur = power(i-j,n) * ncr[i][i-j] % MOD;
			if (j%2) fun[i] -= cur;
			else fun[i] += cur;
		}
		fun[i] %= MOD;
		//cerr << "fun " << i << " : " << fun[i] << endl;
	}

	vector<pii> order;
	for (int i=1; i<=n; i++) {
		cin >> a[i];
		order.push_back({a[i],i});
	}
	sort(order.begin(), order.end());

	for (const pii& it : order) {
		int i = it.second;
		dp[i][1] = 1;
		bit[1].insert(i, 1);
		for (int j=2; j<=n; j++) {
			dp[i][j] = bit[j-1].query(1,i-1);
			bit[j].insert(i, dp[i][j]);
		}
	}

	for (int j=1; j<=n; j++) {
		for (int i=1; i<=n; i++) {
			cnt[j] += dp[i][j];
		}
		cnt[j] %= MOD;
		//cerr << "cnt " << j << " : " << cnt[j] << endl;
	}

	ll ans = 0;
	for (int j=1; j<=n; j++) {
		ans += fun[j] * cnt[j] % MOD;
	}
	cout << (ans % MOD + MOD) % MOD << nl;

	return 0;
}
