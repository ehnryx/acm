#pragma GCC optimize("O3")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#define _USE_MAGIC_IO

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

#ifdef _USE_MAGIC_IO
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
	static char c; x = 0;
	for (c = get(); c < '0' || c > '9'; c = get()) ;
	for (; c >= '0' && c <= '9'; c = get()) x = x * 10 + c - '0';
}
void readchar(char& c) {
	while (isspace(c = get()));
}
// END MAGIC IO
#endif

struct Edge {
	int v, c;
};

const int L = 19;
const int N = 250000 + 1;
struct Tree {
	vector<Edge> adj[N];
	ll len[N];
	int order[N];
	pair<int,int> rmq[L][2*N];

	int sz[N], cdepth[N], cpar[N];
	vector<int> csub[N];

	void input(int n) {
		memset(cdepth, -1, sizeof cdepth);
		for(int i=1; i<n; i++) {
			int a, b, c;
#ifdef _USE_MAGIC_IO
			read(a); read(b); read(c);
#else
			cin >> a >> b >> c;
#endif
			adj[a].push_back({b,c});
			adj[b].push_back({a,c});
		}
	}

	//int lg[2*N + 1];
	void build_rmq() {
		for(int j=1; j<L; j++) {
			for(int i=0; i+(1<<j)<=2*N; i++) {
				rmq[j][i] = min(rmq[j-1][i], rmq[j-1][i+(1<<(j-1))]);
			}
		}
		//for(int i=1; i<=2*N; i++) {
			//lg[i] = 31 - __builtin_clz(i);
		//}
	}

	int lca(int u, int v) {
		int l = min(order[u], order[v]);
		int r = max(order[u], order[v]);
		//int j = lg[r-l+1];
		int j = 31 - __builtin_clz(r-l+1);
		return min(rmq[j][l], rmq[j][r-(1<<j)+1]).second;
	}

	ll distance(int u, int v) {
		int c = lca(u,v);
		return len[u] + len[v] - 2*len[c];
	}

	int rmqid = 0;
	int dfs(int u, int p, int d=0) {
		order[u] = rmqid;
		rmq[0][rmqid++] = make_pair(d, u);
		sz[u] = 1;
		for (const Edge& e : adj[u]) {
			if (e.v != p) {
				len[e.v] = len[u] + e.c;
				sz[u] += dfs(e.v, u, d+1);
				rmq[0][rmqid++] = make_pair(d, u);
			}
		}
		return sz[u];
	}

	int centroid(int u, int p, bool save) {
		for (const Edge& e : adj[u]) {
			int v = e.v;
			if (cdepth[v] == -1 && sz[v] > sz[u]/2) {
				sz[u] -= sz[v];
				sz[v] += sz[u];
				return centroid(v, p, save);
			}
		}
		// at centroid
		cdepth[u] = cdepth[p] + 1;
		cpar[u] = p;
		if(save) csub[u].push_back(u);
		for(const Edge& e : adj[u]) {
			int v = e.v;
			if (cdepth[v] == -1) {
				int cv = centroid(v, u, save);
				//*! to save vertices in subtree
				if(save) {
					for (int it : csub[cv]) {
						csub[u].push_back(it);
					}
				}
				//*/
			}
		}
		return u;
	}

	int decompose(int u, bool save) {
		dfs(u, 0);
		return centroid(u, 0, save);
	}
};

Tree g[2];

vector<pair<ll,int>> obest, osecond;

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	int n;
#ifdef _USE_MAGIC_IO
	read(n);
#else
	cin >> n;
#endif
	for(int i=0; i<2; i++) {
		g[i].input(n);
		g[i].decompose(1, i==0);
		g[i].build_rmq();
	}

	vector<ll> ans(n+1, INFLL);
	obest.resize(n+1, make_pair(INFLL, -1));
	osecond.resize(n+1, make_pair(INFLL, -1));

	for(int i=1; i<=n; i++) {
		for(int u : g[0].csub[i]) {
			for(int j=u; j!=0; j=g[1].cpar[j]) {
				ll cur = g[0].distance(i,u) + g[1].distance(j,u);
				if(cur < obest[j].first) {
					osecond[j] = obest[j];
					obest[j] = make_pair(cur, u);
				} else if(cur < osecond[j].first) {
					osecond[j] = make_pair(cur, u);
				}
			}
		}

		for(int u : g[0].csub[i]) {
			for(int j=u; j!=0; j=g[1].cpar[j]) {
				ll cur = g[0].distance(i,u) + g[1].distance(j,u);
				if(obest[j].second != u) {
					ans[u] = min(ans[u], cur + obest[j].first);
				} else {
					ans[u] = min(ans[u], cur + osecond[j].first);
				}
			}
		}

		for(int u : g[0].csub[i]) {
			for(int j=u; j!=0; j=g[1].cpar[j]) {
				obest[j] = osecond[j] = make_pair(INFLL, -1);
			}
		}
	}

	for(int i=1; i<=n; i++) {
		cout << ans[i] << nl;
	}

	return 0;
}
