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

const int N = 250000 + 1;

struct Tree {
	struct Edge {
		int v, c;
	};

	vector<Edge> adj[N];
	vector<pair<int,ll>> csub[N];
	vector<pair<int,ll>> cpar[N];
	bool vis[N];
	int sz[N];

	Tree() {
		memset(vis, 0, sizeof vis);
	}

	void add_edge(int a, int b, int c) {
		adj[a].push_back({b,c});
		adj[b].push_back({a,c});
	}

	void get_dists(int u, int p, int x, ll d) {
		csub[x].push_back(make_pair(u,d));
		cpar[u].push_back(make_pair(x,d));
		for(const Edge& e:adj[u]) {
			if(e.v!=p && !vis[e.v]) {
				get_dists(e.v, u, x, d+e.c);
			}
		}
	}

	vector<int> seen;
	int dfs(int u, int p) {
		seen.push_back(u);
		sz[u] = 1;
		for(const Edge& e:adj[u]) {
			if(e.v != p && !vis[e.v]) {
				sz[u] += dfs(e.v, u);
			}
		}
		return sz[u];
	}

	int centroid(int u) {
		seen.clear();
		int s = dfs(u, 0);
		for(int v:seen) {
			bool ok = true;
			for(const Edge& e:adj[v]) {
				if(vis[e.v]) continue;
				if(2*sz[v] < s || (sz[v] > sz[e.v] && 2*sz[e.v] > s)) {
					ok = false;
					//break;
				}
			}
			if(ok) {
				get_dists(v, 0, v, 0);
				return v;
			}
		}
		assert(false);
	}

	void decompose(int u) {
		int c = centroid(u);
		vis[c] = true;
		for(const Edge& e:adj[c]) {
			if(!vis[e.v]) {
				decompose(e.v);
			}
		}
	}
};

Tree g[2];

ll ans[N];
pair<ll,int> best[N], second[N];

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	int n;
	cin >> n;
	for(int t=0; t<2; t++) {
		for(int i=1; i<n; i++) {
			int a, b, c;
			cin >> a >> b >> c;
			g[t].add_edge(a,b,c);
		}
		g[t].decompose(n);
	}

	fill(ans, ans+N, INFLL);
	for(int i=1; i<=n; i++) {
		for(const pair<int,ll>& it : g[0].csub[i]) {
			for(const pair<int,ll>& jt : g[1].cpar[it.first]) {
				best[jt.first] = second[jt.first] = make_pair(INFLL, -1);
			}
		}
		for(const pair<int,ll>& it : g[0].csub[i]) {
			for(const pair<int,ll>& jt : g[1].cpar[it.first]) {
				ll cur = it.second + jt.second;
				if(cur < best[jt.first].first) {
					second[jt.first] = best[jt.first];
					best[jt.first] = make_pair(cur, it.first);
				} else if(cur < second[jt.first].first) {
					second[jt.first] = make_pair(cur, it.first);
				}
			}
		}
		for(const pair<int,ll>& it : g[0].csub[i]) {
			for(const pair<int,ll>& jt : g[1].cpar[it.first]) {
				if(it.first != best[jt.first].second) {
					ll cur = best[jt.first].first + it.second + jt.second;
					ans[it.first] = min(ans[it.first], cur);
				} else {
					ll cur = second[jt.first].first + it.second + jt.second;
					ans[it.first] = min(ans[it.first], cur);
				}
			}
		}
	}

	for(int i=1; i<=n; i++) {
		cout << ans[i] << nl;
	}

	return 0;
}
