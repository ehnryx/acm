#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int INF = 0x3f3f3f3f;
const char nl = '\n';

const int MAXN = 505;
const int MAXM = 50005;
int n, m;

int par[MAXN];
int parent(int a) { return par[a] < 0? a : (par[a] = parent(par[a]));}

bool merge(int a, int b) {
	int x = parent(a), y = parent(b);
	if (x==y) return false;
	par[y] = x;
	return true;
}

vector<vector<int>> edges;
int getother(int u, int e) {
	return edges[e][1] == u? edges[e][2]:edges[e][1];
}

vector<int> adj[MAXN];

int rep[MAXM];

bool dfs(int u, int t, int c, int p = -1) {
	if (u==t) return true;
	for(int e: adj[u]) {
		int v=getother(u, e);
		if (v==p) continue;
		if (dfs(v, t, c, u)){
			if (edges[e][0]==c) rep[e]++;
			return true;
		}
	}
	return false;
}


int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	memset(par, -1, sizeof par);
	cin >> n >> m;
	for(int i=0;i<m;i++) {
		int u, v, c;
		cin >> u >> v >> c;
		edges.push_back({c,u,v});
	}
	sort(edges.begin(),edges.end());

	for(int i=0;i<m;i++) {
		int u = edges[i][1];
		int v = edges[i][2];
		if (merge(u,v)) {
			adj[u].push_back(i);
			adj[v].push_back(i);
		}
	}
	for(int i=0;i<m;i++) {
		if(!dfs(edges[i][1], edges[i][2], edges[i][0])) assert(false);
	}
	int br=0;
	int cost=0;
//	for(int i=0;i<m;i++) { cerr << rep[i] << " "; } cerr<<endl;
	for(int i=0;i<m;i++) {
		if (rep[i]==1) {
			br++;
			cost+=edges[i][0];
		}
	}
	cout << br << " " << cost <<endl;

	return 0;
}
