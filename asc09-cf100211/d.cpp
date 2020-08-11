//#pragma GCC optimize("O3")
//#pragma GCC target("sse4,avx2,abm,fma,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#define FILENAME "police"

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
const ll MOD = 998244353;
const ld EPS = 1e-9;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int N = 100 + 1;
namespace SCC {
	int low[N], vis[N], scomp[N], scompNum, I;
	vector<int> adj[N]; stack<int> verts;
	void scc(int u) { low[u] = vis[u] = ++I; verts.push(u);
		for(int v : adj[u]) {
			if(!vis[v]) scc(v);
			if(scomp[v] == -1) low[u] = min(low[u], low[v]);
		}
		if(vis[u] <= low[u]) { int v;
			do { v=verts.top(); verts.pop(); scomp[v]=scompNum; } while (v!=u);
			++scompNum;
		}
	}
	void get_scc(int n) {
		memset(vis, 0, sizeof vis); memset(scomp, -1, sizeof scomp);
		scompNum = I = 0; for(int i=1; i<=n; i++) if(!vis[i]) scc(i);
	}
}

__int128 dp[N][N], ncr[N][N];
int sz[N], in[N], out[N];

// double-check correctness
// read limits carefully
// characterize valid solutions
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);
///*
#ifdef ONLINE_JUDGE
	freopen(FILENAME ".in", "r", stdin);
	freopen(FILENAME ".out", "w", stdout);
#endif
//*/

	for(int i=0; i<N; i++) {
		ncr[i][0] = ncr[i][i] = 1;
		for(int j=1; j<i; j++) {
			ncr[i][j] = ncr[i-1][j] + ncr[i-1][j-1];
		}
	}

	int n, m, k;
	cin >> n >> m >> k;
	for(int i=0; i<m; i++) {
		int a, b;
		cin >> a >> b;
		SCC::adj[a].push_back(b);
	}
	SCC::get_scc(n);

	for(int i=1; i<=n; i++) {
		sz[SCC::scomp[i]+1]++;
		for(int j : SCC::adj[i]) {
			if(SCC::scomp[i] == SCC::scomp[j]) continue;
			out[SCC::scomp[i]+1]++;
			in[SCC::scomp[j]+1]++;
		}
	}

	n = SCC::scompNum;
	dp[0][0] = 1;
	for(int i=1; i<=n; i++) {
		for(int j=0; j<=k; j++) {
			for(int t=(!in[i]||!out[i]); t<=sz[i] && t<=j; t++) {
				dp[i][j] += dp[i-1][j-t] * ncr[sz[i]][t];
			}
		}
	}

	string ans;
	for(__int128 v = dp[n][k]; v; v /= 10) {
		ans.push_back(v % 10 + '0');
	}
	reverse(ans.begin(), ans.end());
	if(ans.empty()) {
		ans.push_back('0');
	}
	cout << ans << nl;

	return 0;
}
