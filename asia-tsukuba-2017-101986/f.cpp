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
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-13;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

namespace BCC {
	const int N = 1e5+1;
	const int M = 1e5+1;
	int vcompNum,ecompNum,I,m;
	int first[N],low[N],vis[N],ecomp[N];
	int nxt[2*M],ep[2*M],vcomp[2*M];
	stack<int> edges, verts;
	void init() { m = 0; memset(first, -1, sizeof(first)); }
	int add_edge(int a, int b) {
		nxt[m] = first[ep[m] = a], first[ep[m]] = m, ++m;
		nxt[m] = first[ep[m] = b], first[ep[m]] = m; ++m;
		return m-2;
	}
	void biconnected(int u, int par){ int v,E; low[u] = vis[u] = ++I; verts.push(u);
		for (int e = first[u]; e != -1; e = nxt[e]) { v = ep[e^1];
			if (!vis[v]) { edges.push(e); biconnected(v,e); low[u] = min(low[u],low[v]);
				if (vis[u] <= low[v]) { // u is a cut vertex unless it's a one-child root
					do { E = edges.top(); edges.pop(); vcomp[E] = vcomp[E^1] = vcompNum; }
					while (e != E && e != (E^1)); ++vcompNum; }}
			else if (vis[v] < vis[u] && e != (par^1)) {
				low[u] = min(low[u], vis[v]); edges.push(e); }
			else if (v == u) vcomp[e] = vcomp[e^1] = vcompNum++; } // e is a self-loop
			if (vis[u] <= low[u]) { // par is a cut edge unless par==-1
				do { v = verts.top(); verts.pop(); ecomp[v] = ecompNum; }
				while (v != u); ++ecompNum; }
	}
	void get_bcc(int n) { memset(vis,0,sizeof vis); vcompNum=ecompNum=I=0;
		for (int i=1; i<=n; ++i) if (!vis[i]) biconnected(i, -1);
	}
	// tree-independent criteria for identifying articulation points and bridges
	bool isCutVertex(int u) { for (int e = first[u]; e != -1; e = nxt[e])
		if (vcomp[e] != vcomp[first[u]]) return true; return false; }
	bool isCutEdge(int e) { return ecomp[ep[e]] != ecomp[ep[e^1]]; }
}

struct Edge {
	int i; ll d;
	bool operator < (const Edge& o) const {
		return d > o.d;
	}
};

const int N = 1e5+1;
vector<Edge> adj[N],rev[N],dag[N];
ll fdist[N], rdist[N];

void dijkstra(int s, vector<Edge> g[], ll d[]) {
	fill(d,d+N,INFLL);
	priority_queue<Edge> dijk;
	dijk.push({s,0});
	while(!dijk.empty()) {
		Edge cur = dijk.top();
		dijk.pop();
		if(d[cur.i] == INFLL) {
			d[cur.i] = cur.d;
			for(const Edge& e:g[cur.i]) {
				if(d[e.i] == INFLL) {
					dijk.push({e.i,e.d+cur.d});
				}
			}
		}
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);

	int n,m;
	cin>>n>>m;
	int S = 1;
	int T = 2;
	int a[m],b[m],c[m];
	for(int i=0;i<m;i++) {
		cin>>a[i]>>b[i]>>c[i];
		adj[a[i]].push_back({b[i],c[i]});
		rev[b[i]].push_back({a[i],c[i]});
	}
	dijkstra(S,adj,fdist);
	dijkstra(T,rev,rdist);
	assert(fdist[T] == rdist[S]);

	string ans[m];
	int idx[m];
	memset(idx,-1,sizeof idx);

	BCC::init();
	for(int i=0;i<m;i++) {
		if(fdist[a[i]] + rdist[b[i]] + c[i] == fdist[T]) {
			idx[i] = BCC::add_edge(a[i],b[i]);
			ans[i] = "SOSO";
		} else {
			if(fdist[b[i]] + rdist[a[i]] + c[i] < fdist[T]) {
				ans[i] = "HAPPY";
			} else {
				ans[i] = "SOSO";
			}
		}
	}
	BCC::get_bcc(n);

	for(int i=0;i<m;i++) {
		if(idx[i]!=-1 && BCC::isCutEdge(idx[i])) {
			ans[i] = "SAD";
		}
		cout<<ans[i]<<nl;
	}

	return 0;
}
