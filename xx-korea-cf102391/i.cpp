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

const int N = 500+1;
ll adj[N][N], dist[N][N];
pair<ll,int> sd[N][N];

pair<ll,ll> solve_edge(int n, int u, int v) {
	ll maxu = 0;
	ll maxv = 0;
	for(int i=1; i<=n; i++) {
		maxu = max(maxu, dist[u][i]);
		maxv = max(maxv, dist[v][i]);
	}
	ll best = 2 * min(maxu, maxv);
	ll split = 2 * (maxu < maxv ? 0 : adj[u][v]);
	vector<bool> donej(n+1);
	for(int i=n,j=1; i>=1; ) {
		assert(!donej[sd[u][i].second]);
		while(j<=n && sd[v][j].second != sd[u][i].second) {
			donej[sd[v][j].second] = true;
			j++;
		}
		if(j>n) break;
		donej[sd[v][j].second] = true;
		while(i>=1 && donej[sd[u][i].second]) {
			i--;
		}
		if(i<1) break;
		ll x = adj[u][v] + sd[v][j].first - sd[u][i].first;
		assert(0 <= x && x <= 2*adj[u][v]);
		ll cur = 2*sd[u][i].first + x;
		if(cur < best) {
			best = cur;
			split = x;
		}
	}
	return make_pair(best, split);
}

vector<pii> build_tree(int n, int u, int v, ll d, ll x) {
	ll du = x;
	ll dv = 2*adj[u][v] - x;
	vector<pii> tree;
	tree.push_back(pii(u,v));
	vector<bool> done(n+1);
	done[u] = done[v] = true;
	for(int e=2; e<n; e++) {
		pii edge;
		ll best = INFLL;
		for(int i=1; i<=n; i++) {
			if(done[i]) continue;
			for(int j=1; j<=n; j++) {
				if(!done[j]) continue;
				ll cur = min(du + 2*dist[u][j] + 2*adj[j][i], dv + 2*dist[v][j] + 2*adj[j][i]);
				if(cur < best) {
					best = cur;
					edge = pii(i,j);
				}
			}
		}
		tree.push_back(edge);
		done[edge.first] = true;
	}
	assert(tree.size() == n-1);
	return tree;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	int n, m;
	cin >> n >> m;

	fill(&adj[0][0], &adj[0][0]+N*N, INFLL);
	for(int i=1; i<=n; i++) {
		adj[i][i] = 0;
	}
	vector<pii> edges;
	for(int i=0; i<m; i++) {
		int a,b,c;
		cin >> a >> b >> c;
		adj[a][b] = adj[b][a] = c;
		edges.push_back(pii(a,b));
	}

	for(int i=1; i<=n; i++) {
		for(int j=1; j<=n; j++) {
			dist[i][j] = adj[i][j];
		}
	}

	for(int k=1; k<=n; k++) {
		for(int i=1; i<=n; i++) {
			for(int j=1; j<=n; j++) {
				dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
			}
		}
	}

	for(int i=1; i<=n; i++) {
		for(int j=1; j<=n; j++) {
			sd[i][j] = make_pair(dist[i][j], j);
		}
		sort(sd[i]+1, sd[i]+n+1);
	}

	ll best = INFLL;
	ll split = -1;
	pii center;
	for(const auto& e:edges) {
		ll cur, res;
		tie(cur, res) = solve_edge(n, e.first, e.second);
		if(cur < best) {
			best = cur;
			split = res;
			center = e;
		}
	}
	assert(split != -1);
	cerr<<"got center "<<center.first<<" "<<center.second<<" and split "<<split<<nl;

	cout << best << nl;
	for(const auto& e : build_tree(n, center.first, center.second, best, split)) {
		cout << e.first << " " << e.second << nl;
	}

	return 0;
}
