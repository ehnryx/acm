#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;

const int MAXN = 1e5+10;
int n, m;
set<int> adj[MAXN];

int vis[MAXN];
int nex[MAXN];

int gid = 0;
int id[MAXN];
int low[MAXN];

int col[MAXN];

bool dfs(int u, int pathcol=1, int parpathcol=0) {
	bool ans = true;
	vis[u] = 1;
	id[u] = gid++;
	col[u] = pathcol;
	if (nex[u]) ans|=dfs(nex[u], pathcol, parpathcol);

	for(int v:adj[u]) {
		if (v==nex[u]) continue;
		if (vis[v]) {
			if(pathco
		}
		else {
		}
	}
	return ans;
}


bool dfs1(int u, int T) {
	if (u==T) return true;
	vis[u] = 1;
	for(int v: adj[u]) {
		if (!vis[v]) {
			if (dfs1(v, T)) {
				nex[u] = v;
				return true;
			}
		}
	}
	return false;
}

int dfs2(int u) {
	if (u==T) return true;
	vis[u] = 1;
	for(int v: adj[u]) {
		if (!vis[v]) {
			int T= dfs2(v);
			nex[u] = v;
			return T;
		}
	}
	return v;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin >> n >> m;
	for(int i=0;i<m;i++) {
		cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	vector<int> degone;
	for(int i=1;i<=n;i++) {
		if (adj[i].size()==1) degone.push_back(i);
	}
	if (degone.size()>2) {
		cout << "No" <<endl;
		return 0;
	}
	int S = -1, T = -1;
	if (degone.size()>0) {
		S = degone[0];
	}
	else {
		S = 1;
	}
	if (degone.size()>1) {
		T = degone[1];
		dfs1(S,T);
	}
	else {
		T = dfs2(S);
	}

	memset(vis, 0, sizeof vis);
	if (!dfs(S)) { // failed condition
		cout << "No" <<endl;
		return 0;
	}
// check connected
  for(int i=1;i<=n;i++) {
		if (!vis[i]) {
			cout << "No" <<endl;
			return 0;
		}
	}

	cout << "Yes" <<endl;


	return 0;
}
