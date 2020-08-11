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
	const int N = 3e2+2;
	const int M = N*N;
	int par[N], first[N], nxt[2*M], ep[2*M], m;
	ll flo[2*M], cap[2*M], cost[2*M];
	void init() { m = 0; memset(first,-1,sizeof first); memset(flo,0,sizeof flo); }
	void add_edge(int a, int b, ll c=1, ll p=0) { //a,b - nodes, c, p - cap, price
		nxt[m] = first[ep[m]=a], first[ep[m]] = m, cap[m] = c, cost[m] =  p, ++m;
		nxt[m] = first[ep[m]=b], first[ep[m]] = m, cap[m] = 0, cost[m] = -p, ++m; }
	int L[N], cur[N];
	bool bfs(int s, int t) {
		memset(L, INF, sizeof L);
		queue<int> q; q.push(s); L[s] = 0;
		while (!q.empty()) { int u = q.front(); q.pop();
			for (int v, e = cur[u] = first[u]; e != -1; e = nxt[e])
				if (L[v=ep[e^1]] == INF && flo[e] < cap[e])
					q.push(v), L[v] = L[u]+1;
		} return L[t] < INF; }
	ll dfs(int u, int t, ll f) {
		if (u == t) return f;
		ll cf, df = 0;
		for (int v, e = cur[u]; e != -1 && df < f; cur[u] = e = nxt[e])
			if (flo[e] < cap[e] && L[v=ep[e^1]] == L[u]+1) {
				cf = dfs(v, t, min(cap[e]-flo[e], f-df));
				flo[e] += cf; flo[e^1] -= cf; df += cf;
			} return df; }
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);

	int n,m,k;
	cin>>n>>m>>k;
	Flow::init();
	const int T = n+m+k+1;
	for(int i=1;i<=n;i++) {
		int r;
		cin>>r;
		Flow::add_edge(0,i);
		for(int j=0;j<r;j++) {
			int v;
			cin>>v;
			Flow::add_edge(i,v+n);
		}
	}
	set<int> seen;
	for(int i=1;i<=k;i++) {
		int r;
		cin>>r;
		for(int j=0;j<r;j++) {
			int v;
			cin>>v;
			Flow::add_edge(v+n,i+n+m);
			seen.insert(v);
		}
		int c;
		cin>>c;
		Flow::add_edge(i+n+m,T,c);
	}
	for(int i=1;i<=m;i++) {
		if(!seen.count(i)) {
			Flow::add_edge(i+n,T);
		}
	}

	ll ans = 0;
	while(Flow::bfs(0,T)) {
		ans += Flow::dfs(0,T,INF);
	}
	cout<<ans<<nl;

	return 0;
}
