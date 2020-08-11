#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef pair<ld,ld> pdd;
typedef complex<ld> pt;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-13;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

ll power(ll n, int e) {
	ll r = 1;
	for(;e;e/=2) {
		if(e&1) r = r*n % MOD;
		n = n*n % MOD;
	}
	return r;
}

const int N = 1<<18;
int a[N];
ll sum[N];
vector<int> cars[N];
int bit[N];
void insert(int x, int v) {
	for(; x<N; x+=x&-x) {
		bit[x] += v;
	}
}
int query(int x) {
	int res = 0;
	for(; x>0; x-=x&-x) {
		res += bit[x];
	}
	return res;
}
int query_range(int l, int r) {
	return query(r) - query(l-1);
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	int n, m;
	ll k;
	cin >> n >> m >> k;
	for(int i=1; i<=n; i++) {
		cin >> a[i];
		sum[i] = sum[i-1] + a[i];
	}

	for(int i=0; i<m; i++) {
		int l, r;
		cin >> l >> r;
		cars[l].push_back(r);
	}

	ll ans = 0;
	for(int i=1; i<=n; i++) {
		auto r = lower_bound(sum, sum+n+1, sum[i-1] + k);
		if(r == sum+n+1) continue;
		int any = query_range(r-sum, n);
		for(int j : cars[i]) {
			insert(j, 1);
		}
		int cur = query_range(r-sum, n) - any;
		ans += power(2, any) * (power(2, cur) + MOD-1) % MOD;
	}
	ans %= MOD;

	cout << ans << nl;

	return 0;
}
