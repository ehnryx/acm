#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef int ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

namespace Flow {
	const int N = 500;
  // data structures and helper functions common to all flow routines
  struct Edge { int v, r; ll f, c; };
  vector<Edge> adj[N]; int sz[N]; ll mc;
  void add_edge(int a, int b, ll c=1) { mc = max(mc,c);  // scaling
    adj[a].push_back({b,sz[b]++,0,c}); // mcf_edges.push_back({b,a,0,c,p});
    adj[b].push_back({a,sz[a]++,0,0}); }

  // Dinic O(V^2E) in general, O(sqrt(V)E) on unit caps
  // O(VElog(C)) with scaling (C = max edge cap) but worse constant factor
  // USAGE: 1) add edges 2) flow(S, T, scaling?);
  // not proven to be floating point safe, worked on naipc 2015 F;  try this:
  // flow = 0; for(int it=0; it<K && bfs(s,t,EPS); it++) flow += dfs(s,t,inf);
  int L[N], cur[N], Q[N];
  bool bfs(int s, int t, ll lim=1) {
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
    ll res = 0; for(ll lim=(scaling?mc:1); lim; lim/=2) {
      while(bfs(s,t,lim)) res += dfs(s,t,inf); } return res; }
}

struct Edge {
	int a,b,c;
};

//#define FILEIO
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);
#ifdef FILEIO
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#endif

	int n,m,s,t;
	cin>>n>>m>>s>>t;
	for(int i=0;i<m;i++) {
		int a,b,c;
		cin>>a>>b>>c;
		Flow::add_edge(a,b,c);
	}

	ll f = Flow::flow(s,t,true);
	int id = 0;
	Edge ans[m];
	for(int i=0;i<n;i++) {
		for(const Flow::Edge& e:Flow::adj[i]) {
			if(e.f>0) {
				ans[id++] = {i,e.v,e.f};
			}
		}
	}

	cout<<n<<" "<<f<<" "<<id<<nl;
	for(int i=0;i<id;i++) {
		cout<<ans[i].a<<" "<<ans[i].b<<" "<<ans[i].c<<nl;
	}

	return 0;
}
