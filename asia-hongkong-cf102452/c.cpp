#include <bits/stdc++.h>
using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

using ll = long long;
using ld = long double;
#define nl '\n'

const int N = 2e5 + 1;
int val[N];
vector<int> adj[N];
bool vis[N];
int sz[N];
vector<tuple<int,ll,int>> dists[N];  // m, d, i
int subs[N];

void get_dists(int u, int p, int x, int m, ll d, int i) {
	m = max(m, val[u]);
	d = d + val[u];
	dists[x].push_back(make_tuple(m, d, i));
	for(int v : adj[u]) {
		if(v == p || vis[v]) continue;
		get_dists(v, u, x, m, d, i);
	}
}

int dfs(int u, int p, vector<int>& seen) {
	seen.push_back(u);
	sz[u] = 1;
	for(int v : adj[u]) {
		if(v == p || vis[v]) continue;
		sz[u] += dfs(v, u, seen);
	}
	return sz[u];
}

int centroid(int u) {
	vector<int> seen;
	int s = dfs(u, 0, seen);
	for(int v : seen) {
		if(2*sz[v] < s) continue;
		bool ok = true;
		for(int w : adj[v]) {
			if(!vis[w] && sz[w] < sz[v] && 2*sz[w] > s) {
				ok = false;
				break;
			}
		}
		if(ok) {
			int m = val[v];
			int d = val[v];
			int cid = 0;
			for(int w : adj[v]) {
				if(vis[w]) continue;
				get_dists(w, v, v, m, d, ++cid);
			}
			subs[v] = cid;
			return v;
		}
	}
	assert(false);
}

void decompose(int u) {
	int c = centroid(u);
	vis[c] = true;
	for(int v : adj[c]) {
		if(vis[v]) continue;
		decompose(v);
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);

	int T;
	cin >> T;
	while(T--) {
		int n;
		cin >> n;
		for(int i=1; i<=n; i++) {
			cin >> val[i];
			adj[i].clear();
			dists[i].clear();
			vis[i] = false;
		}
		for(int i=1; i<n; i++) {
			int a, b;
			cin >> a >> b;
			adj[a].push_back(b);
			adj[b].push_back(a);
		}
		decompose(1);

		ll ans = 0;
		for(int c=1; c<=n; c++) {
			if(subs[c] == 0) continue;
			sort(dists[c].begin(), dists[c].end(), greater<tuple<int,ll,int>>());
			int uid = 0;
			vector<ordered_set<pair<ll,int>>> seen(subs[c] + 1);
			for(auto [m, d, i] : dists[c]) {
				if(2*m < d) {
					ans++;
				}
				ans += seen[0].order_of_key(make_pair(d, 0));
				ans -= seen[i].order_of_key(make_pair(d, 0));
				seen[0].insert(make_pair(2*m - d + val[c], ++uid));
				seen[i].insert(make_pair(2*m - d + val[c], ++uid));
			}
		}
		cout << ans << nl;
	}

	return 0;
}
