#include<bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;
const int MAXN = 1e5+10;
const int MAXD = 18;

vector<pii> adj[MAXN];
vector<int> ch[MAXN];
int par[MAXN][MAXD];
int mind[MAXN];
int maxe[MAXN][MAXD];
int depth[MAXN];
int done[MAXN];

map<pii, int> edges;
int n, r;

int query(int u, int v) {
	if (u==v) return 0;
	if (depth[u] < depth[v]) swap(u,v);
	int ans = 0;
	// u is too deep move it up to v
	//cerr << "MOVE TO SAME" << u << " " << v <<endl;
	for(int i=MAXD-1;i>=0;i--) {
		if(depth[u] - (1<<i) >=depth[v]) {
			//cerr << u << " " << i <<" " <<par[u][i] << endl;
			ans = max(ans, maxe[u][i]);
			u = par[u][i];
		}
	}
	// both u and v are at same depth
	assert(depth[u]==depth[v]);
	if (u==v) return ans;
	// move them up so that u==v
	//cerr << "MOVE UP " << u << " " << v <<endl;
	for(int i=MAXD-1;i>=0;i--) {
		if(par[u][i]!=par[v][i]) {
			ans = max(ans, maxe[u][i]);
			ans = max(ans, maxe[v][i]);
			u = par[u][i];
			v = par[v][i];
		}
	}
	if (u==v) return ans;
	// parents should be lca
	assert(par[u][0]==par[v][0]);
	ans = max(ans, maxe[u][0]);
	ans = max(ans, maxe[v][0]);
	return ans;
}
const bool gen = 0;

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
	cin >> n >> r;
	for(int i=0;i<r;i++) {
		int u, v, w;
		if (!gen) cin >> u >> v >> w;
		else {
			if (i < n) u = i+1, v = i+2, w = rand()%10000+1;
			else u = rand()%n, v = rand()%n,  w = rand()%10000+1;
		}
		adj[u].emplace_back(v,w);
		adj[v].emplace_back(u,w);
		if (u>v) swap(u,v);
		edges[pii(u,v)] = w;
	}
	priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>> > q;
	q.push({0,1});
	memset(par,-1,sizeof par);
	memset(mind,0x3f, sizeof mind);
	mind[1] = 0;
	depth[1] = 0;
	int ocost = 0;
	while(!q.empty()) {
		int w = q.top().first;
		int u = q.top().second;
		q.pop();
		if (done[u]) continue;
		//cerr << "@ " << u <<endl;
		done[u] = 1;
		maxe[u][0] = w;
		ocost+=w;
		for(int i=1;i<MAXD;i++) {
			if (par[u][i-1]==-1) break;
			par[u][i] = par[par[u][i-1]][i-1];
			maxe[u][i] = max(maxe[u][i-1], maxe[par[u][i-1]][i-1]); 
		}
		//if (par[u][0]!=-1) ch[par[u][0]].push_back(u);
		for(auto &p: adj[u]) {
			int v = p.first;
			int nw = p.second;
			//cerr << "GOING TO "<< v << " " << nw <<endl;
			if (!done[v] && mind[v] > nw) {
				depth[v] = depth[u]+1;
				mind[v] = nw;
				par[v][0] = u;
				q.push({nw, v});
			}
		}
	}
	//cerr << "TREE DONE " << ocost <<endl;
	int Q;
	cin >> Q;
	for(int i=0;i<Q;i++) {
		int u, v;
		if (!gen) {
			cin >> u >> v;
		}
		else {
			u = 1;
			v = 2;
		}
		if (u>v) swap(u,v);
		//cerr << edges[pii(u,v)] << " " << query(u,v) <<endl;
		cout << ocost+edges[pii(u,v)]-query(u,v) <<'\n';
	}
}
