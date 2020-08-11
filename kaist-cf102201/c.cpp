#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int MOD = 993244853;
const char nl = '\n';

const int N = 5e4 + 1;
vector<int> adj[N];

// START DECOMPOSITION

int par[N];
unordered_set<int> skip[N];
bool vis[N];

vector<int> tree[2*N], cycle[2*N];
vector<int> cyc[2*N];

void get_cycle(int u, int p, int cid) {
	cycle[u].push_back(cid);
	cyc[cid].push_back(u);
	for(int v=p; v!=u; v=par[v]) {
		cyc[cid].push_back(v);
	}
}

int build(int u, int p, int& cid) {
	if(vis[u]) {
		get_cycle(u, p, ++cid);
		skip[u].insert(p);
		return u;
	}

	assert(par[u] == 0);
	par[u] = p;
	vis[u] = true;
	int wait = 0;
	for(int v : adj[u]) {
		if(v == p || skip[u].count(v)) continue;
		int to = build(v, u, cid);
		if(!to) {
			tree[u].push_back(v);
		} else if(to != u) {
			assert(!wait);
			wait = to;
		}
	}
	return wait;
}

// END DECOMPOSITION

// START MODULAR

int add(int a, int b) {
	return (a+b < MOD ? a+b : a+b-MOD);
}
int mul(int a, int b) {
	return (ll)a*b % MOD;
}
int power(int n, int e) {
	int res = 1;
	for(;e;e/=2) {
		if(e&1) res = mul(res, n);
		n = mul(n, n);
	}
	return res;
}
int inverse(int n) {
	assert(n != 0);
	return power(n, MOD-2);
}
int debug(int x) {
	return x<MOD/2 ? x : x-MOD;
}

// END MODULAR


int solve(int, int);
int solve_cycle(int, int);

int dp[2*N][2], cp[N][2];

int solve(int u, int t) {
	if(dp[u][t] != -1) return dp[u][t];

	int all = 1;
	int need = 0;
	bool istree = true;
	for(int v : tree[u]) {
		int cur = solve(v, 0);
		if(cur == 0) {
			if(need) return dp[u][t] = 0;
			need = v;
		} else {
			all = mul(all, cur);
		}
	}
	for(int v : cycle[u]) {
		int cur = solve_cycle(v, 1);
		if(cur == 0) {
			if(need) return dp[u][t] = 0;
			need = v;
			istree = false;
		} else {
			all = mul(all, cur);
		}
	}
	if(t) {
		return dp[u][t] = (need ? 0 : all);
	}

	if(need) {
		if(istree) {
			return dp[u][t] = mul(all, MOD - solve(need, 1));
		} else {
			return dp[u][t] = mul(all, solve_cycle(need, 0));
		}
	}

	int res = 0;
	for(int v : tree[u]) {
		int cur = mul(MOD - solve(v, 1), inverse(solve(v, 0)));
		res = add(res, mul(cur, all));
	}
	for(int v : cycle[u]) {
		int cur = mul(solve_cycle(v, 0), inverse(solve_cycle(v, 1)));
		res = add(res, mul(cur, all));
	}
	return dp[u][t] = res;
}

int solve_cycle(int u, int t) {
	if(dp[u][t] != -1) return dp[u][t];
	int sz = cyc[u].size();
	assert(sz >= 3);

	for(int i=1; i<sz; i++) {
		solve(cyc[u][i], 0);
		solve(cyc[u][i], 1);
	}

	cp[0][0] = 0;
	cp[0][1] = 1;
	for(int i=1; i<sz; i++) {
		cp[i][0] = mul(cp[i-1][1], solve(cyc[u][i], 1));
		cp[i][1] = mul(cp[i-1][1], solve(cyc[u][i], 0));
		cp[i][1] = add(cp[i][1], MOD - mul(cp[i-1][0], solve(cyc[u][i], 1)));
	}
	if(t) {
		return dp[u][t] = cp[sz-1][1];
	}

	int left = mul(cp[sz-2][1], MOD - solve(cyc[u][sz-1], 1));
	cp[1][0] = 0;
	cp[1][1] = 1;
	for(int i=2; i<sz; i++) {
		cp[i][0] = mul(cp[i-1][1], solve(cyc[u][i], 1));
		cp[i][1] = mul(cp[i-1][1], solve(cyc[u][i], 0));
		cp[i][1] = add(cp[i][1], MOD - mul(cp[i-1][0], solve(cyc[u][i], 1)));
	}
	int right = mul(cp[sz-1][1], MOD - solve(cyc[u][1], 1));
	int all = mul(2, sz%2 ? 1 : MOD-1);
	for(int i=1; i<sz; i++) {
		all = mul(all, solve(cyc[u][i], 1));
	}
	return dp[u][t] = add(all, add(left, right));
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	int n, m;
	cin >> n >> m;
	for(int i=0; i<m; i++) {
		int a, b;
		cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	int cid = n;
	build(1, 0, cid);

	//cerr<<"decomposed: "<<nl; for(int i=1; i<=n; i++) {
	//cerr<<i<<" -> "<<nl;
	//cerr<<" tree:  "; for(int j:tree[i]) //cerr<<j<<" ";
	//cerr<<nl;
	//cerr<<" cycle: "; for(int j:cycle[i]) //cerr<<j<<" ";
	//cerr<<nl; }
	//cerr<<nl;

	//cerr<<"cycles: "<<nl; for(int i=n+1; i<=cid; i++) {
	//cerr<<i<<" -> "; for(int j:cyc[i]) //cerr<<j<<" ";
	//cerr<<nl; }
	//cerr<<nl;

	memset(dp, -1, sizeof dp);
	cout << solve(1, 0) % MOD << nl;
	//cerr<<"answer: "<<debug(solve(1,0))<<nl;

	return 0;
}
