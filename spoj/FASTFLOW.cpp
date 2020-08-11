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

namespace Flow {
	const int N = 5e3;
	const int M = 3e4;
	struct Edge { int v, r; ll f, c; };
	vector<Edge> adj[N]; int sz[N]; ll mc;
	void init(int n=N) { mc=0; fill(sz,sz+n,0); fill(adj,adj+n,vector<Edge>()); }
	void add_edge(int a, int b, ll c) { mc = max(mc,c);
		adj[a].push_back({b, sz[b]++, 0, c});
		adj[b].push_back({a, sz[a]++, 0, c}); }
	int L[N], cur[N], Q[N];
	bool bfs(int s, int t, int lim=1) {
		memset(L, INF, sizeof L); memset(cur, 0, sizeof cur);
		int f,b; Q[f=b=0] = s; L[s] = 0; while(f<=b) { int u = Q[f++]; 
			for(const Edge& e:adj[u]) if(L[e.v] == INF && e.c-e.f >= lim) {
				Q[++b] = e.v; L[e.v] = L[u]+1; } } return L[t] < INF; }
	ll dfs(int u, int t, ll f) { if (u == t) return f;
		ll df = 0; for (int i = cur[u]; i < sz[u] && df < f; cur[u] = ++i) {
			Edge& e = adj[u][i]; if (e.f < e.c && L[e.v] == L[u]+1) {
				ll cf = dfs(e.v, t, min(e.c-e.f, f-df)); 
				if(cf) { e.f += cf; adj[e.v][e.r].f -= cf; df += cf; } } } return df; }
	ll flow(int s, int t, bool scaling=false) { ll inf=numeric_limits<ll>::max();
		ll res = 0; for(int lim=(scaling?mc:1); lim; lim/=2) {
			while(bfs(s,t,lim)) res += dfs(s,t,inf); } return res; }
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	int n,m;
	cin>>n>>m;
	for(int i=0;i<m;i++) {
		int a,b,c;
		cin>>a>>b>>c;
		Flow::add_edge(a-1,b-1,c);
	}
	cout<<Flow::flow(0,n-1,true)<<nl;

	return 0;
}
