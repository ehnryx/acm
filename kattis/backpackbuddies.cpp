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
	int i,d,p;
	Edge() {}
	Edge(int _i, int _d, int _p=0): i(_i), d(_d), p(_p) {}
	bool operator < (const Edge& o) const {
		if(d!=o.d) return d > o.d;
		else return p > o.p;
	}
};

const int N = 1e5+1;
vector<Edge> adj[N];
int dist[N];

int fast(int s, int t) {
	memset(dist,INF,sizeof dist);
	priority_queue<Edge> dijk;
	dijk.push(Edge(s,0));
	while(!dijk.empty()) {
		Edge cur = dijk.top();
		dijk.pop();
		if(dist[cur.i]<INF) continue;
		dist[cur.i] = cur.d;
		for(const Edge& e:adj[cur.i]) {
			if(dist[e.i]<INF) continue;
			dijk.push(Edge(e.i,e.d+cur.d));
		}
	}
}

int slow(int s, int t) {
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);

	int n,m;
	cin>>n>>m;
	for(int i=0;i<m;i++) {
		int a,b,c;
		cin>>a>>b>>c;
		adj[a].push_back(Edge(b,c));
		adj[b].push_back(Edge(a,c));
	}
	cout<<fast(0,n-1)-slow(0,n-1)<<nl;

	return 0;
}
