//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma")
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
typedef complex<ld> pt;

const char nl = '\n';
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-11;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int N = 2e3 + 1;
vector<int> adj[N];
int cnt[N];
ll dp[3*N], ndp[3*N], up[N];

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	int n;
	cin >> n;
	vector<pair<int,int>> edges;
	for(int i=1; i<n; i++) {
		int a, b;
		cin >> a >> b;
		adj[a].push_back(edges.size());
		edges.push_back(make_pair(a,b));
		adj[b].push_back(edges.size());
		edges.push_back(make_pair(b,a));
	}
	for(int i=1; i<=n; i++) {
		if(adj[i].size() > 1) {
			edges.push_back(make_pair(0, i));
		}
	}
	int m = edges.size();

	ll ans = 0;
	bool ok = true;
	for(int k=2; k<n && ok; k++) {
		fill(dp, dp+m, 1);
		ok = false;
		for(int sz=k; sz<n; sz*=k) {
			// count number of candidates
			for(int v=1; v<=n; v++) {
				cnt[v] = 0;
				for(int e : adj[v]) {
					cnt[v] += (dp[e] > 0);
				}
			}
			// only check when cnt >= k
			for(int i=0; i<m; i++) {
				auto [a, b] = edges[i];
				if(cnt[b] < k || adj[a].size() == 1) {
					ndp[i] = 0;
					continue;
				}
				fill(up, up+k+1, 0);
				up[0] = 1;
				int id = 0;
				for(int j : adj[b]) {
					if(edges[j].second == a || dp[j] == 0) continue;
					for(int c=id; c>=0; c--) {
						up[c+1] = (up[c+1] + up[c]*dp[j]) % MOD;
					}
					if(id<k-1) id++;
				}
				ndp[i] = up[k];
				if(a == 0) {
					ok |= (ndp[i] > 0);
					ans += ndp[i];
				}
			}
			ans %= MOD;
			swap(dp, ndp);
		}
	}

	cout << (ans + n) % MOD << nl;

	return 0;
}
