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

struct Node {
	int u; ld d;
	bool operator < (const Node& o) const {
		return d > o.d;
	}
};

const int N = 2e5+1;
vector<int> adj[N];
ld best[N], dist[N], cmul[N], tval[N];

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	int n, m;
	cin >> n >> m;
	for(int i=0; i<m; i++) {
		int a, b;
		cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}

	fill(cmul, cmul+N, 1);
	fill(best, best+N, INF);
	fill(dist, dist+N, -7);

	priority_queue<Node> dijk;
	dijk.push({n, 0});
	while(!dijk.empty()) {
		Node cur = dijk.top();
		dijk.pop();
		if(dist[cur.u] > -1) continue;
		dist[cur.u] = cur.d;
		for(int v : adj[cur.u]) {
			if(dist[v] > -1) continue;
			if(cur.d > best[v]+(ld)2/3) continue;
			best[v] = min(best[v], cur.d);
			tval[v] += ((ld)3/4 * (1 + cur.d) + (ld)1/4) * cmul[v];
			cmul[v] *= (ld)1/4;
			ld d = tval[v] + (2 + best[v]) * cmul[v];
			dijk.push({v, d});
		}
	}

	//cerr<<"results: "<<nl; for(int i=1; i<=n; i++) {
	//cerr<<i<<": best "<<best[i]<<"  tval "<<tval[i]<<"  dist "<<dist[i]<<nl; }
	//cerr<<nl;

	cout << dist[1] << nl;

	return 0;
}
