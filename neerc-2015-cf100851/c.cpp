#include <bits/stdc++.h>
using namespace std;
#define FILENAME "cactus"

#define nl '\n'
typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;

const int N = 1e5+10, M = 1e5+10;
int sz[N], fsz[N];
set<int> adj[N];
namespace BCC {
int vcompNum, ecompNum, I, m;
int first[N], low[N], vis[N], ecomp[N];
int nxt[2*M], ep[2*M], vcomp[2*M];
stack<int> edges, verts;
void init() { m = 0; memset(first, -1, sizeof first); }
void add_edge(int a, int b) {
	nxt[m] = first[ep[m] = a], first[ep[m]] = m, ++m;
	nxt[m] = first[ep[m] = b], first[ep[m]] = m, ++m; }
void biconnected(int u, int par) { int v, E; low[u] = vis[u] = ++I; verts.push(u);
	for (int e = first[u]; e != -1; e = nxt[e]) { v = ep[e^1];
		if (!vis[v]) { edges.push(e); biconnected(v, e); low[u] = min(low[u], low[v]);
			if (vis[u] <= low[v]) {
				do { E = edges.top(); edges.pop(); vcomp[E] = vcomp[E^1] = vcompNum; }
				while (e != E && e != (E^1)); ++ vcompNum; }}
		else if (vis[v] < vis[u] && e != (par^1)) {
			low[u] = min(low[u], vis[v]); edges.push(e); }
		else if (v == u) vcomp[e] = vcomp[e^1] = vcompNum++; }
	if (vis[u] <= low[u]) {
		do { v = verts.top(); verts.pop(); ecomp[v] = ecompNum; }
		while (v != u); ++ecompNum; }
}
char iscv[N];
void get_bcc(int n) { memset(vis, 0, sizeof vis); vcompNum = ecompNum = I = 0; memset(iscv, -1, sizeof iscv);
	for (int i = 0; i < n; i++) if (!vis[i]) biconnected(i, -1);
}
bool isCutVertex(int u) { if (iscv[u] != -1) return iscv[u];
	for (int e = first[u]; e != -1; e = nxt[e])
	if (vcomp[e] != vcomp[first[u]]) return iscv[u] = 1; return iscv[u] = 0; }
bool isCutEdge(int e) { return ecomp[ep[e]] != ecomp[ep[e^1]]; }
}

int n, m; 
vector<int> interesting;
int tsz[N];
ll ans=0;

void dfs(int u, int par=-1) {
	interesting.push_back(u);
	if (u >= n) {
		for (int i : adj[u]) {
			if (i < n) fsz[u-n]--;
		}
		tsz[u] = fsz[u-n];
	} else {
		tsz[u] = 1;
	}
	for (int i : adj[u]) {
		if (i == par) continue;
		dfs(i, u);
		tsz[u] += tsz[i];
	}
	if (u<n && par!=-1 && par < n) {
		ans+=(ll)tsz[u]*(n-tsz[u]) - 1;
	}
}

int vis[N];
vector<int> adjvcomp;
ll adjtree[N];
ll sumt[N];

int dfs2(int u) {
	vis[u] = 1;
	int ans = 1;
	for(int i : adj[u]) {
		if (vis[i]) continue;
		if (i>=n) {
			adjvcomp.push_back(i-n);
		}
		else {
			ans+=dfs2(i);
		}
	}
	return ans;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
#ifdef ONLINE_JUDGE
	freopen(FILENAME ".in", "r", stdin);
	freopen(FILENAME ".out", "w", stdout);
#endif
	
	cin >> n >> m;
	if (n == 1) {
		puts("0");
		return 0;
	}
	BCC::init();
	for (int i = 0; i < m; i++) {
		int k; cin >> k;
		int prev; cin >> prev; prev--;
		for (int j = 1; j < k; j++) {
			int u; cin >> u; u--;
			BCC::add_edge(prev, u);
			prev = u;
		}
	}
	BCC::get_bcc(n);
	int root = -1;
	{
		using namespace BCC;
		for (int i = 0; i < BCC::m; i += 2) {
			sz[vcomp[i]]++;
			fsz[vcomp[i]]++;
		}
		for (int e = 0; e < BCC::m; e += 2) {
			if (sz[vcomp[e]] > 1) {
				if (isCutVertex(ep[e])) {
					adj[n+vcomp[e]].insert(ep[e]);
					adj[ep[e]].insert(n+vcomp[e]);
					root = ep[e];
				}
				if (isCutVertex(ep[e^1])) {
					adj[n+vcomp[e]].insert(ep[e^1]);
					adj[ep[e^1]].insert(n+vcomp[e]);
					root = ep[e^1];
				}
			} else {
				adj[ep[e]].insert(ep[e^1]);
				adj[ep[e^1]].insert(ep[e]);
				root = ep[e];
			}
		}
	}
	if (root == -1) {
		cout << (ll) n * (((ll) n * (n-1) / 2) - n) << nl;
		return 0;
	}
	dfs(root);
	//cerr << ans <<endl;
	ll tot = 0;
	for(int i : interesting) {
		if (i < n && !vis[i]) {
			adjvcomp.clear();
			ll sszz = dfs2(i);
			ll contribution = sszz*(sszz-1)/2 - (sszz-1);
			tot+=contribution;
			for(int j:adjvcomp) {
				//cerr << " j " << j << " real: " << i << " sz: " << sszz << endl;
				adjtree[j]+=sszz;
				sumt[j] += contribution;
			}
		}
	}
	for(int i : interesting) {
		if (i>=n) {
			i = i-n;
			ll totsz = fsz[i] + adjtree[i];
			//cerr << " inter " << i << " " << totsz << " cact size " << sz[i] <<endl;
			ans+= sz[i]*(tot-sumt[i]+totsz*(totsz-1)/2 - totsz);
		}
	}
	cout << ans <<endl;

	return 0;
}
