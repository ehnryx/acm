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

const int N = 300 + 2;
int g[N][N], id[N][N];
ll fact[N*N], invf[N*N];
bool before[N][N][N];

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	fact[0] = invf[0] = 1;
	for(int i=1; i<N*N; i++) {
		fact[i] = fact[i-1] * i % MOD;
		invf[i] = inverse(fact[i]);
	}

	int m, n;
	cin >> m >> n;

	for(int i=1; i<=m; i++) {
		for(int j=1; j<=n; j++) {
			cin >> g[i][j];
			id[i][g[i][j]] = j;
		}
		g[i][n+1] = id[i][n+1] = n+1;
		for(int j=0; j<=n+1; j++) {
			for(int k=0; k<j; k++) {
				before[i][g[i][j]][g[i][k]] = true;
			}
		}
	}

	ll ans = 0;
	ll dp[n+2], sum[n+2][n+2], prod[n+2][n+2];
	unordered_set<int> cur[n+2];
	for(int s=1; s<=m; s++) {
		// solve [s,...]
		for(int i=0; i<=n+1; i++) {
			cur[g[s][i]].clear();
			for(int j=0; j<i; j++) {
				sum[g[s][i]][g[s][j]] = i-j-1;
				prod[g[s][i]][g[s][j]] = invf[i-j-1];
				cur[g[s][i]].insert(g[s][j]);
			}
		}

		for(int t=s+1; t<=m; t++) {
			for(int v=1; v<=n+1; v++) {
				for(auto it=cur[v].begin(); it!=cur[v].end(); ) {
					if(before[t][v][*it]) {
						int add = id[t][v] - id[t][*it] - 1;
						sum[v][*it] += add;
						prod[v][*it] = prod[v][*it] * invf[add] % MOD;
						it++;
					} else {
						it = cur[v].erase(it);
					}
				}
			}

			fill(dp, dp+n+2, 0);
			for(int i=1; i<=n+1; i++) {
				// match g[s][i]
				int v = g[s][i];
				dp[v] = fact[sum[v][0]] * prod[v][0] % MOD;
				for(auto it=cur[v].begin(); it!=cur[v].end(); it++) {
					dp[v] -= dp[*it] * fact[sum[v][*it]] % MOD * prod[v][*it] % MOD;
				}
				dp[v] = (dp[v] % MOD + MOD) * fact[t-s+1] % MOD;
			}
			ans += dp[n+1] * invf[t-s+1] % MOD;
		}
	}

	ans = (ans % MOD + MOD) % MOD;
	cout << ans << nl;

	return 0;
}
