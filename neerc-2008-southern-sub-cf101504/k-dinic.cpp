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

const int N = 50;
namespace Flow {
  // data structures and helper functions common to all flow routines
  struct Edge { int v, r; ll f, c, p; };
  vector<Edge> adj[N]; int sz[N]; ll mc;
  void init(int n=N) { mc=0; fill(sz,sz+n,0); fill(adj,adj+n,vector<Edge>()); }
  void add_edge(int a, int b, ll c=1, ll p=0) { mc = max(mc,c);
    adj[a].push_back({b, sz[b]++, 0, c, p});
    adj[b].push_back({a, sz[a]++, 0, c, -p}); }  // change 0 to c for undirected

  // Dinic O(V^2E) in general, O(sqrt(V)E) on unit caps
  // O(VElog(C)) with scaling (C = max edge cap) but worse constant factor
  // USAGE: 1) add edges 2) flow(S, T, scaling?);
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

int adj[N][N];

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	int n,m;
	cin>>n>>m;
	int a[m],b[m],c[m];
	for(int i=0;i<m;i++) {
		cin>>a[i]>>b[i]>>c[i];
		--a[i]; --b[i];
		adj[a[i]][b[i]] = adj[b[i]][a[i]] = i+1;
	}

	vector<int> ans;
	int best = INF;
	for(int i=0;i<n;i++) {
		int s = !i;
		for(int j=0;j<n;j++) {
			if(j==i || j==s) continue;
			Flow::init();
			for(int e=0;e<m;e++) {
				if(a[e]!=i && b[e]!=i) {
					Flow::add_edge(a[e],b[e],c[e]);
				}
			}
			int cur = Flow::flow(s,j);
			if(cur < best) {
				best = cur;
				ans.clear();
				for(int k=0;k<n;k++) {
					for(const Flow::Edge& e:Flow::adj[k]) {
						if(Flow::L[k]<INF && Flow::L[e.v]==INF) {
							ans.push_back(adj[e.v][k]);
						}
					}
				}
			}
		}
	}

	cout<<best<<nl;
	cout<<ans.size()<<nl;
	for(int it:ans) {
		cout<<it<<" ";
	}
	cout<<nl;

	return 0;
}
