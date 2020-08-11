#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;

const char nl = '\n';
const int INF = 0x3f3f3f3f;

const int N = 256;
const int M = 3*555;


vector<pair<int,int>> adj[N];
map<int,int> remap;
set<int> sat;

struct Flow {
	int par[N], first[N], nxt[2*M], ep[2*M], m, eid[2*M];
	ll flo[2*M], cap[2*M], cost[2*M];
	bool vis[N];
	void init() {
		 m=0; memset(first, -1, sizeof first); memset(flo, 0, sizeof flo);
		 memset(vis,0,sizeof vis);
	}
	void add_edge(int a, int b, ll c =1, ll id = -1) {
		nxt[m] = first[ep[m]=a], first[ep[m]] = m, cap[m] = c, eid[m] = id, ++m;
		nxt[m] = first[ep[m]=b], first[ep[m]] = m, cap[m] = 0, eid[m] = id, ++m;
	}

	ll mf_update(int s, int t, ll del=1) {
		ll df[N]; memset(df, 0, sizeof df); memset(par, -1, sizeof par);
		queue<int> q; q.push(s); par[s] = -2; df[s] = INF;
		while(!q.empty()) {
			ll cf; int u = q.front(); q.pop();
			for(int v, e = first[u]; e!=-1;e=nxt[e])
				if (par[v=ep[e^1]] == -1 && (cf = cap[e]-flo[e]) >= del)
					q.push(v), par[v] = e, df[v] = min(df[u], cf);
		}
		if (par[t]==-1) return 0;
		for(int e, i = t;i!=s;i=ep[e])
			e = par[i], flo[e] += df[t], flo[e^1] -= df[t];
		return df[t];
	}
} flow;


struct Mincut {
	int data[N][N], dist[N], done[N], ans, best, ind, a, b, c, n, m, t;
	int erased;
	void init(int erase, int _n) {
		memset(data,0,sizeof data); ans = INF;
		erased = erase;
		for(int i=0;i<_n;i++) {
			if (i==erase) continue;
			for(auto &p: adj[i]) {
				int j = p.second;
				int cost = p.first;
				if (j==erase) continue;
				//cerr << i-(i>erase) << " " << j-(j>erase) << " " << cost << " add edge " <<endl;
				//cerr << i << " " << j << " " << erase <<endl;
				data[i-(i>erase)][j-(j>erase)]+= cost;
			}
		}
		n = _n-1;
	}
	pair<int,int> bestp;
	int solve() {
		int ba = -1;
		int bb = -1;
		while(n>1) {
			memset(dist,0,sizeof dist); memset(done,0,sizeof done);
			for(int i=0;i<n;i++) { 
				best = ind = -1;
				for(int j=0;j<n;j++) if (!done[j] && dist[j] > best) best = dist[j], ind = j;
				if(i+2 ==n) a = ind;
				if(i+1 ==n) {
					b = ind;
					if (ans > best) {
						ans = best;
						ba = a+(a>=erased);
						bb = b+(b>=erased);
					}
				}
				done[ind] = 1;
				for(int j=0;j<n;j++) dist[j] += data[ind][j];
			}
			if (a>b) swap(a,b);
			for(int i=0;i<n;i++) data[a][i]+=data[b][i], data[i][a]+=data[i][b];
			for(int i=0;i<n;i++) data[b][i]+=data[n-1][i], data[i][b]+=data[i][n-1];
			n--;
		}
		bestp = make_pair(ba,bb);
		return ans;
	}
} mincut;


int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int _n, _m;
	cin >> _n >> _m;
	vector<vector<int>> edges;
	for(int i=0;i<_m;i++) {
		int u, v, w;
		cin >> u >> v >> w;
		u--; v--;
		edges.push_back({u,v,w});
		adj[u].push_back({w,v});
		adj[v].push_back({w,u});
	}
	int best = INF;
	int brem = -1;
	pair<int,int> bp(-1,-1);
	for(int i=0;i<_n;i++) {
		mincut.init(i,_n);
		mincut.solve();
		//cerr << " removing " << i << " " << mincut.ans << " " << mincut.bestp.first << " " << mincut.bestp.second <<endl;
		if (mincut.ans < best) {
			best = mincut.ans;
			bp = mincut.bestp;
			brem = i;
		}
	}
	assert(bp.first!=-1);

	flow.init();
	int S = bp.first;
	int T = bp.second;
	// add edges here!
	int id = 0;
	for(auto &v: edges) {
		id++;
		if (v[0] == brem || v[1] == brem) continue;
		flow.add_edge(v[0], v[1], v[2], id);
		flow.add_edge(v[1], v[0], v[2], id);
	}
	ll fff  = 0;
	for(ll del = INF;del;del/=2) while(ll df = flow.mf_update(S,T, del)) fff+=df;
	assert(fff == best);

	cout << fff <<endl;
	for (int e = 0; e < flow.m; e++) {
		if (flow.par[flow.ep[e]] != -1 && flow.par[flow.ep[e^1]] == -1) {
			//if (sat.count(flow.eid[e])) sat.remove(
			sat.insert(flow.eid[e]);
		}
	}
	cout << sat.size() << endl;
	for(int i: sat) {
		cout << i << " ";
	}
	cout <<endl;
	return 0;
}
