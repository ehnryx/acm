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

const ll P = 17;

ll power(ll n, ll e, ll m) {
	ll res = 1;
	for(;e;e/=2) {
		if(e&1) res = res*n % m;
		n = n*n % m;
	}
	return res;
}

const int N = 1<<17;
ll st[2*N], z[2*N], base[2*N];

void build() {
	ll x = 1;
	for(int i=0;i<N;i++) {
		base[N+i] = x;
		x = x*P % MOD;
	}
	for(int i=N-1; i>0; i--) {
		st[i] = (st[2*i] + st[2*i+1]) % MOD;
		base[i] = (base[2*i] + base[2*i+1]) % MOD;
	}
}

void push(int i) {
	if(z[i]) {
		st[2*i] = base[2*i] * z[i] % MOD;
		st[2*i+1] = base[2*i+1] * z[i] % MOD;
		z[2*i] = z[2*i+1] = z[i];
		z[i] = 0;
	}
}

void pull(int i) {
	st[i] = (st[2*i] + st[2*i+1]) % MOD;
}

void update(int l, int r, int v, int i=1, int s=0, int e=N-1) {
	if(r<s || e<l) return;
	if(l<=s && e<=r) {
		z[i] = v;
		st[i] = v * base[i] % MOD;
		return;
	}
	push(i);
	int m = (s+e)/2;
	update(l,r,v,2*i,s,m);
	update(l,r,v,2*i+1,m+1,e);
	pull(i);
}

ll query(int l, int r, int i=1, int s=0, int e=N-1) {
	if(r<s || e<l) return 0;
	if(l<=s && e<=r) {
		return st[i];
	}
	push(i);
	int m = (s+e)/2;
	return query(l,r,2*i,s,m) + query(l,r,2*i+1,m+1,e);
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	int n,m,k;
	cin >> n >> m >> k;

	string s;
	cin >> s;

	ll x = 1;
	for (int i=0;i<n;i++) {
		int v = s[i] - '0' + 3;
		st[i+N] = v*x % MOD;
		x = x*P % MOD;
	}
	build();

	for (int i=0;i<m+k;i++) {
		int t;
		cin >> t;
		if(t == 1) {  // update
			int l, r, v;
			cin >> l >> r >> v;
			--l; --r;
			update(l, r, v+3);
		} else {  // query
			int l, r, d;
			cin >> l >> r >> d;
			--l; --r;
			int len = (r-l+1) - d;
			ll left = query(l, l + len-1) % MOD * power(P, d, MOD) % MOD;
			ll right = query(l+d, l+d + len-1) % MOD;
			if(left == right) {
				cout << "YES" << nl;
			} else {
				cout << "NO" << nl;
			}
		}
	}

	return 0;
}
