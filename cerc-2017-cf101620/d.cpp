#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include <ext/rope>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_cxx;
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

const int N = 2e3+1;
int g[N][N];
int adj[N][N];
int wrap[N];
int cyc[N], len[N], dist[N];

int n,m;
int nexti(int i) { return (i==n ? 1 : i+1); }
int previ(int i) { return (i==1 ? n : i-1); }
int nextj(int j) { return (j==m ? 1 : j+1); }
int prevj(int j) { return (j==1 ? m : j-1); }

bool dfs(int u, int d) {
	if(cyc[u]) {
		if(cyc[u]==-1) {
			cyc[u] = u;
			len[u] = d - dist[u];
			return true;
		} else {
			return false;
		}
	}

	int v = wrap[u];
	cyc[u] = -1;
	len[u] = INF;
	dist[u] = d;
	if(dfs(v, d+1)) {
		if(cyc[u] == -1) {
			cyc[u] = u;
			len[u] = len[v];
			return true;
		} else {
			return false;
		}
	} else {
		cyc[u] = INF;
		return false;
	}
}

void build_cycs() {
	memset(cyc, 0, sizeof cyc);
	for(int i=1;i<=n;i++) {
		if(!cyc[i]) {
			dfs(i, 0);
		}
	}
}

void update_adj(int a, int b) {
	int nb = nextj(b);
	if(g[nexti(a)][nb] > max(g[a][nb], g[previ(a)][nb])) {
		adj[a][b] = nexti(a);
	} else if(g[a][nb] > max(g[nexti(a)][nb], g[previ(a)][nb])) {
		adj[a][b] = a;
	} else {
		adj[a][b] = previ(a);
	}
}

void update(int a, int b) {
	int goal = a;
	for(int j=b; j<=m; j++) {
		goal = adj[goal][j];
	}

	int lb = a;
	int ub = a;
	int cnt = 1;
	for(int j=b-1; j>0; j--) {
		int nlb = nexti(lb);
		int plb = previ(lb);
		int nub = nexti(ub);
		int pub = previ(ub);
		if(adj[plb][j] == lb) {
			lb = plb;
			cnt++;
		} else if(adj[lb][j] != plb) {
		} else {
			lb = nlb;
			cnt--;
		}
		if(adj[nub][j] == ub) {
			ub = nub;
			cnt++;
		} else if(adj[ub][j] != nub) {
		} else {
			ub = pub;
			cnt--;
		}
		if(cnt <= 0) {
			return;
		}
	}

	assert((ub+n-lb) % n == cnt-1);
	for(int i=0; i<cnt; i++) {
		wrap[lb] = goal;
		lb = nexti(lb);
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	cin>>n>>m;

	for(int i=1;i<=n;i++) {
		for(int j=1;j<=m;j++) {
			cin>>g[i][j];
		}
	}

	for(int i=1;i<=n;i++) {
		for(int j=1;j<=m;j++) {
			int nj = nextj(j);
			if(g[nexti(i)][nj] > max(g[i][nj], g[previ(i)][nj])) {
				adj[i][j] = nexti(i);
			} else if(g[i][nj] > max(g[nexti(i)][nj], g[previ(i)][nj])) {
				adj[i][j] = i;
			} else {
				adj[i][j] = previ(i);
			}
		}
	}

	for(int i=1;i<=n;i++) {
		int u = i;
		for(int j=1;j<=m;j++) {
			u = adj[u][j];
		}
		wrap[i] = u;
	}
	build_cycs();

	int x = 1;
	int y = 1;

	int q;
	cin>>q;
	while(q--) {
		string s;
		cin>>s;

		if(s=="move") {
			int k;
			cin>>k;
			for(; k>0 && y!=1; k--) {
				x = adj[x][y];
				y = nextj(y);
			}
			int c = k/m;
			for(; c>0 && cyc[x]!=x; c--) {
				x = wrap[x];
			}
			for(c %= len[x]; c>0; c--) {
				x = wrap[x];
			}
			for(k %= m; k>0; k--) {
				x = adj[x][y];
				y = nextj(y);
			}
			cout<<x<<" "<<y<<nl;
		}

		else {
			int a,b,e;
			cin>>a>>b>>e;
			g[a][b] = e;
			int pb = prevj(b);
			int pa = previ(a);
			int na = nexti(a);
			update_adj(pa, pb);
			update_adj(na, pb);
			update_adj(a, pb);
			update(pa, pb);
			update(na, pb);
			update(a, pb);
			build_cycs();
		}
	}

	return 0;
}
