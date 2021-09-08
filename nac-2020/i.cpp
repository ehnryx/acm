#pragma GCC optimize("O3")
#pragma GCC target("sse4,avx2,abm,fma")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
const char nl = '\n';
const ll MOD = 998244353;
const ll INF = MOD*MOD;

const int S = 5;
const int M = (1<<S) - 1;

int get(const ll& v, int i) {
	return v >> (i*S) & M;
}

void setv(ll& v, int i, int val) {
	if(val > M) cerr<<"val: "<<val<<nl;
	assert(val <= M);
	v ^= (ll)(get(v, i) ^ val) << (i*S);
}

ll add(const ll& a, const ll& b) {
	if(a+b > INF) return (a+b) % MOD;
	return a+b;
}

ll mul(const ll& a, const ll& b) {
	if(a < INF/b) return a*b;
	return (a % MOD) * (b % MOD);
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);

	string s;
	int d;
	cin >> s >> d;
	int n = s.size();

	vector<pair<char,int>> seen;
	for(char c='A'; c<='Z'; c++) {
		if(s.find(c) != -1) {
			seen.push_back(make_pair(c, 1));
		}
	}
	seen.push_back(make_pair('$', 26 - seen.size()));

	unordered_map<ll,ll> dp, nxt;
	ll cur = 0;
	for(int i=0; i<=n; i++) {
		cur |= (ll)i << (i*S);
	}
	dp[cur] = 1;

	ll ans = (get(cur, n) == d);
	for(int row=1; row<=n+d; row++) {
		nxt.clear();
		for(const auto& [vec, cnt] : dp) {
			for(const auto& [c, m] : seen) {
				int minv = M;
				setv(cur, 0, get(vec, 0) + 1);
				for(int i=1; i<=n; i++) {
					if(c == s[i-1]) {
						setv(cur, i, min(get(vec, i-1), min(get(cur, i-1), get(vec, i)) + 1));
					} else {
						setv(cur, i, min(get(vec, i-1), min(get(cur, i-1), get(vec, i))) + 1);
					}
					minv = min(minv, get(cur, i));
				}
				if(minv <= 10) nxt[cur] = add(nxt[cur], mul(cnt, m));
				if(get(cur, n) == d) ans = add(ans, mul(cnt, m));
			}
		}
		swap(dp, nxt);
	}
	cout << ans % MOD << nl;

	return 0;
}
