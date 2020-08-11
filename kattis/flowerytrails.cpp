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

struct Edge {
	int i,d;
	bool operator < (const Edge& o) const {
		return d > o.d;
	}
};

const int N = 1e4+1;
vector<Edge> adj[N];
int from[N], to[N];

void dijkstra(int s, int d[]) {
	fill(d,d+N,INF);
	priority_queue<Edge> dijk;
	dijk.push({s,0});
	while(!dijk.empty()) {
		Edge cur = dijk.top();
		dijk.pop();
		if(d[cur.i]<INF) continue;
		d[cur.i] = cur.d;
		for(const Edge& e:adj[cur.i]) {
			if(d[e.i]<INF) continue;
			dijk.push({e.i,e.d+cur.d});
		}
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout << fixed << setprecision(10);

	int n,m;
	cin>>n>>m;
	for(int i=0;i<m;i++) {
		int a,b,c;
		cin>>a>>b>>c;
		adj[a].push_back({b,c});
		adj[b].push_back({a,c});
	}
	dijkstra(0,from);
	dijkstra(n-1,to);

	int ans = 0;
	for(int i=0;i<n;i++) {
		for(const Edge& e:adj[i]) {
			if(from[i]+to[e.i]+e.d == to[0]) {
				ans += e.d;
			}
		}
	}
	cout<<ans*2<<nl;

	return 0;
}
