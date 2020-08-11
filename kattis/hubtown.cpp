#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef double ld;
typedef int ll;

#define nl '\n'
const int INF = 0x3f3f3f3f;
const ld EPS = 1e-13;

// MAGIC IO
inline char get(void) {
	static char buf[100000], *S = buf, *T = buf;
	if (S == T) {
		T = (S = buf) + fread(buf, 1, 100000, stdin);
		if (S == T) return EOF;
	}
	return *S++;
}
inline void read(int &x) {
	static char c; x = 0; int sgn = 0;
	for (c = get(); c < '0' || c > '9'; c = get()) if (c == '-') sgn = 1;
	for (; c >= '0' && c <= '9'; c = get()) x = x * 10 + c - '0';
	if (sgn) x = -x;
}
void readchar(char& c) {
	while (isspace(c = get()));
}
// END MAGIC IO

namespace Flow {
	const int N = 4e5+2;
	const int M = 1e6;
	struct Edge { int v, r; ll f, c; };
	vector<Edge> adj[N]; int sz[N]; ll mc;
	void init(int n=N) { mc=0; fill(sz,sz+n,0); fill(adj,adj+n,vector<Edge>()); }
	void add_edge(int a, int b, ll c=1) { mc = max(mc,c);
		adj[a].push_back({b, sz[b]++, 0, c});
		adj[b].push_back({a, sz[a]++, 0, 0}); }
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

const int N = 2e5+1;
int a[N],b[N],c[N];

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	int n,m;
	//cin>>n>>m;
	read(n);read(m);
	for(int i=0;i<n;i++) {
		//cin>>a[i]>>b[i];
		read(a[i]);read(b[i]);
	}
	vector<pair<ld,int>> line;
	for(int i=0;i<m;i++) {
		int x,y;
		//cin>>x>>y>>c;
		read(x);read(y);read(c[i]);
		line.push_back(make_pair(atan2(y,x),i));
	}
	sort(line.begin(),line.end());

	const int S = n+m;
	const int T = S+1;
	for(int i=0;i<n;i++) {
		ld ang = atan2(b[i],a[i]);
		auto it = lower_bound(line.begin(),line.end(),make_pair(ang,-1));
		const auto& nxt = (it==line.end() ? line[0] : *it);
		const auto& pre = (it==line.begin() ? line.back() : *prev(it));
		ld to_nxt = abs(nxt.first-ang);
		if(to_nxt > M_PI) to_nxt = 2*M_PI - to_nxt;
		ld to_pre = abs(pre.first-ang);
		if(to_pre > M_PI) to_pre = 2*M_PI - to_pre;
		if(abs(to_nxt - to_pre) < EPS) {
			Flow::add_edge(i, nxt.second+n);
			Flow::add_edge(i, pre.second+n);
			if(c[nxt.second]-->0) Flow::add_edge(nxt.second+n, T);
			if(c[pre.second]-->0) Flow::add_edge(pre.second+n, T);
		} else if(to_nxt < to_pre) {
			Flow::add_edge(i, nxt.second+n);
			if(c[nxt.second]-->0) Flow::add_edge(nxt.second+n, T);
		} else {
			Flow::add_edge(i, pre.second+n);
			if(c[pre.second]-->0) Flow::add_edge(pre.second+n, T);
		}
		Flow::add_edge(S, i);
	}

	{
		using namespace Flow;
		cout<<flow(S,T,true)<<nl;
		for(int i=0;i<n;i++) {
			for(const Edge& e:adj[i]) {
				if(e.f && e.v!=S) {
					cout<<i<<" "<<e.v-n<<nl;
				}
			}
		}
	}

	return 0;
}
