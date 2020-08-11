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

namespace Flow {
	const int N = 50+2;
	struct Edge { int v,r; ll f,c,p; };
	vector<Edge> adj[N]; int sz[N];
	void init(int n=N) { fill(sz,sz+n,0); fill(adj,adj+n,vector<Edge>()); }
	void add_edge(int a, int b, ll c=1, ll p=0) {
		adj[a].push_back({b,sz[b]++,0,c,p});
		adj[b].push_back({a,sz[a]++,0,0,-p});
	}

	bool vis[N]; int par[N]; ll pot[N], dist[N];
	void pot_init(int n) { fill(pot,pot+n,0); }
	int mcf(int s, int t, ll& price, int n) {
		fill(vis,vis+n,0); fill(dist,dist+n,INF); dist[s]=0;
		for(int u=s;u!=-1;) { vis[u]=true; for(const Edge& e:adj[u]) {
			if(e.f<e.c && dist[e.v]>dist[u]+pot[u]-pot[e.v]+e.p) {
				dist[e.v] = dist[u]+pot[u]-pot[e.v]+e.p; par[e.v] = e.r; } }
			u = -1; ll best=INF;
			for(int i=0;i<n;i++) if(!vis[i] && dist[i]<best) best = dist[u=i];
		}
		if(dist[t]>=INF) { return 0; } ll df=INF;
		for(int u=t; u!=s; ) { const Edge& r = adj[u][par[u]];
			df = min(df, adj[r.v][r.r].c - adj[r.v][r.r].f); u = r.v; }
		for(int u=t; u!=s; ) { Edge& r = adj[u][par[u]], &e=adj[r.v][r.r];
			e.f += df; r.f -= df; price += df*e.p; u = r.v; }
		for(int i=0;i<n;i++) {pot[i] = min(INF,dist[i]+pot[i]);} return df;
	}
	void flow(int s, int t, ll& price, int n=N) {
		pot_init(n); price = 0; while(mcf(s,t,price,n));
	}
}

const int N = 50;
int dist[N][N];
int deg[N];

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	int T;
	cin>>T;
	while(T--) {
		int n,m;
		cin>>n>>m;
		memset(dist,INF,sizeof dist);
		memset(deg,0,sizeof deg);

		ll tot = 0;
		for(int i=0;i<m;i++) {
			int a,b,c;
			cin>>a>>b>>c;
			--a; --b;
			dist[a][b] = min(dist[a][b], c);
			deg[a]++; deg[b]--;
			tot += c;
		}

		for(int k=0;k<n;k++) {
			for(int i=0;i<n;i++) {
				for(int j=0;j<n;j++) {
					dist[i][j] = min(dist[i][j], dist[i][k]+dist[k][j]);
				}
			}
		}
		bool bad = false;
		for(int i=0;i<n;i++) {
			for(int j=0;j<n;j++) {
				if(dist[i][j]==INF) bad = true;
			}
		}
		if(bad) {
			cout<<-1<<nl;
			continue;
		}

		const int s = n;
		const int t = n+1;
		Flow::init(n+2);
		for(int i=0;i<n;i++) {
			if(deg[i]<0) {
				Flow::add_edge(s,i,abs(deg[i]),0);
				for(int j=0;j<n;j++) {
					if(deg[j]>0 && dist[i][j]<INF) {
						Flow::add_edge(i,j,min(-deg[i],deg[j]),dist[i][j]);
					}
				}
			} else if(deg[i]>0) {
				Flow::add_edge(i,t,abs(deg[i]),0);
			}
		}
		ll ans = 0;
		Flow::flow(s,t,ans,n+2);
		cout<<tot+ans<<nl;
	}

	return 0;
}
