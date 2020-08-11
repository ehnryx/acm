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
	const int N = 1e3+4;
	const int M = N*2;
	int par[N], first[N], nxt[2*M], ep[2*M], m;
	ll flo[2*M], cap[2*M], cost[2*M];
	void init() { m = 0; memset(first,-1,sizeof first); memset(flo,0,sizeof flo); }
	void add_edge(int a, int b, ll c=1, ll p=0) { //a,b - nodes, c, p - cap, price
		nxt[m] = first[ep[m]=a], first[ep[m]] = m, cap[m] = c, cost[m] =  p, ++m;
		nxt[m] = first[ep[m]=b], first[ep[m]] = m, cap[m] = 0, cost[m] = -p, ++m; }
	int q[N], inq[N];
#define BUBL { \
	t = q[i]; q[i] = q[j]; q[j] = t; \
	t = inq[q[i]]; inq[q[i]] = inq[q[j]]; inq[q[j]] = t; }
	bool vis[N]; ll pot[N], dist[N];
	void mcf_pot_init(int n) { memset(pot, 0, sizeof pot);
		// if all edge costs >= 0, we can safely return before the Bellman-Ford here
		for (int k = 1; k < n; ++k) for (int e = 0; e < m; ++e)
			if (cap[e]) pot[ep[e^1]] = min(pot[ep[e^1]], pot[ep[e]] + cost[e]); }
	ll mcf_update(int s, int t, ll& price, int n) {
		memset(vis, 0, sizeof vis); memset(dist, INF, sizeof dist); dist[s] = 0;
		memset(inq, -1, sizeof inq);
		int qs = 0; inq[q[qs++] = s] = 0;
		while (qs) {
			int u = q[0]; inq[u] = -1;
			q[0] = q[--qs];
			if( qs ) inq[q[0]] = 0;
			for( int i = 0, j = 2*i + 1, t; j < qs; i = j, j = 2*i + 1 ) {
				if( j + 1 < qs && dist[q[j + 1]] < dist[q[j]] ) j++;
				if( dist[q[j]] >= dist[q[i]] ) break;
				BUBL; }
			if (vis[u] == 1) continue; vis[u] = 1;
			for (int e = first[u]; e != -1; e = nxt[e]) { int v = ep[e^1];
				if (flo[e] < cap[e] && dist[v] > dist[u] + pot[u] - pot[v] + cost[e]) {
					dist[v] = dist[u] + pot[u] - pot[v] + cost[e], par[v] = e;
					if( inq[v] < 0 ) { inq[q[qs] = v] = qs; qs++; }
					for( int i = inq[v], j = ( i - 1 )/2, t;
							dist[q[i]] < dist[q[j]]; i = j, j = ( i - 1 )/2 )
						BUBL;
				}
			}
		}
		if (dist[t] >= INF) return 0; ll df = INF;
		for (int e, i = t; i != s; i = ep[e])
			e = par[i], df = min(df, cap[e] - flo[e]);
		for (int e, i = t; i != s; i = ep[e])
			e = par[i], flo[e] += df, flo[e^1] -= df, price += df*cost[e];
		for (int i = 0; i < n; ++i) pot[i] = min(INF, dist[i] + pot[i]);
		return df; }
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);

	Flow::init();

	int p,n,m;
	cin>>p>>n>>m;
	const int s = n+2;
	const int t = n+3;
	for(int i=0;i<m;i++) {
		int a,b;
		cin>>a>>b;
		Flow::add_edge(a+2,b+2,1,1);
		Flow::add_edge(b+2,a+2,1,1);
	}
	Flow::add_edge(s,0,p);
	Flow::add_edge(1,t,p);

	Flow::mcf_pot_init(n+4);
	ll ans = 0;
	ll flow = 0;
	while(ll df=Flow::mcf_update(s,t,ans,n+4)) {
		flow += df;
	}

	if(flow<p) {
		cout<<p-flow<<" people left behind"<<nl;
	} else {
		cout<<ans<<nl;
	}

	return 0;
}
