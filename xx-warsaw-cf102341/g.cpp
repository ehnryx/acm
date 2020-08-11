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

const int N = 20;
int dp[N][1<<N];
int solve(int n, int bm) {
	if(n <= 0) return 0;
	if(dp[n-1][bm] != -1) return dp[n-1][bm];
	ll seen = 0;
	for(int i=0; i<n; i++) {
		if(bm&1<<i) {
			// III -> I.I
			int res = solve(i, bm&((1<<i)-1)) ^ solve(n-1-i, bm>>(i+1));
			seen |= 1LL<<res;
			// III -> II.
			seen |= 1LL<<solve(n, bm^1<<i);
		} else {
			// II. -> .I.
			int res = 0;
			if(i>0) res ^= solve(i-1, bm&((1<<(i-1))-1));
			res ^= solve(n-2-i, bm>>(i+2));
			if(i>0 && bm&1<<(i-1)) res ^= 1;
			if(i+1<n && bm&1<<(i+1)) res ^= 1;
			seen |= 1LL<<res;
		}
	}
	for(int i=0; i<=2*n; i++) {
		if(!(seen & 1LL<<i)) {
			return dp[n-1][bm] = i;
		}
	}
	assert(false);
}

int calc(const vector<string>& s, int l, int r) {
	if(l > r) return 0;
	int bm = 0;
	for(int i=l; i<=r; i++) {
		if(s[i] == ".I.") {
			int res = calc(s, l, i-2) ^ calc(s, i+2, r);
			res ^= (i > l && s[i-1] == "III");
			res ^= (i < r && s[i+1] == "III");
			return res;
		} else if(s[i] == "I.I") {
			int res = calc(s, l, i-1) ^ calc(s, i+1, r);
			return res;
		} else if (s[i] == "III") {
			bm |= 1<<(i-l);
		}
	}
	return solve(r-l+1, bm);
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	memset(dp, -1, sizeof dp);

	int T;
	cin >> T;
	while (T--) {
		int n;
		cin >> n;
		vector<string> s(n);
		for(int i=0; i<n; i++) {
			cin >> s[i];
		}
		int ans = calc(s, 0, n-1);
		if(ans) cout << "First" << nl;
		else cout << "Second" << nl;
	}

	return 0;
}
