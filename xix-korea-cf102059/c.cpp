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

ll power(ll n, ll e) {
	ll res = 1;
	for(;e;e/=2) {
		if(e&1) res = res*n % MOD;
		n = n*n % MOD;
	}
	return res;
}

ll inverse(ll n) {
	return power(n, MOD-2);
}

const int N = 5e3+2;
ll dpl[N][N], dpr[N][N];

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	int n, r, h;
	cin >> n >> r >> h;

	ll invrh = inverse(r+h);
	ll rdie = r*invrh % MOD;
	ll hdie = h*invrh % MOD;

	string s;
	cin >> s;

	int a, b;
	cin >> a >> b;

	dpl[0][b] = 1;
	for(int i=1; i<=n; i++) {
		for(int j=0; j<=n; j++) {
			if(s[i-1] == 'H') {
				dpl[i][j] = dpl[i-1][j+1];
			} else if(j>0) {
				dpl[i][j] = (dpl[i-1][j] * rdie + dpl[i][j-1] * hdie) % MOD;
			}
		}
	}

	dpr[n+1][a] = 1;
	for(int i=n; i>=1; i--) {
		for(int j=0; j<=n; j++) {
			if(s[i-1] == 'R') {
				dpr[i][j] = dpr[i+1][j+1];
			} else if(j>0) {
				dpr[i][j] = (dpr[i+1][j] * hdie + dpr[i][j-1] * rdie) % MOD;
			}
		}
	}

	ll ans = 0;
	for(int i=0; i<=n; i++) {
		ans += dpl[i][0] * dpr[i+1][0] % MOD;
	}
	ans = (ans % MOD + MOD) % MOD;
	cout << ans << nl;

	return 0;
}
