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

struct Edge {
	int i,d;
	bool operator < (const Edge& o) const {
		return d > o.d;
	}
};

const int N = 5e4+1;
const int S = 500;
vector<Edge> adj[N],rev[N];
vector<int> to[N],fr[N];

void build(int n, int s, vector<Edge> g[], vector<int> d[]) {
	d[s] = vector<int>(n,INF);
	priority_queue<Edge> dijk;
	d[s][s] = 0;
	dijk.push({s,0});
	while(!dijk.empty()) {
		Edge cur = dijk.top();
		dijk.pop();
		if(cur.d > d[s][cur.i]) continue;
		for(const Edge& e:g[cur.i]) {
			if(e.d+cur.d < d[s][e.i]) {
				d[s][e.i] = e.d+cur.d;
				dijk.push({e.i,d[s][e.i]});
			}
		}
	}
}

int solve(int s, int t, int k) {
	vector<int> dist(t-s+2*k, INF);
	priority_queue<Edge> dijk;
	dist[s-s] = 0;
	dijk.push({s,0});
	while(!dijk.empty()) {
		Edge cur = dijk.top();
		dijk.pop();
		if(cur.d > dist[cur.i-s]) continue;
		if(cur.i == t) return cur.d;
		if(cur.i/k >= t/k) continue;
		for(const Edge& e:adj[cur.i]) {
			if(e.d+cur.d < dist[e.i-s]) {
				dist[e.i-s] = e.d+cur.d;
				dijk.push({e.i,dist[e.i-s]});
			}
		}
	}
	return -1;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	int k,n,m,q;
	cin>>k>>n>>m>>q;
	for(int i=0;i<m;i++) {
		int a,b,t;
		cin>>a>>b>>t;
		adj[a].push_back({b,t});
		rev[b].push_back({a,t});
	}

	for(int i=0;i*k<n;i+=S) {
		for(int j=0;j<k&&i*k+j<n;j++) {
			build(n,i*k+j,adj,fr);
			build(n,i*k+j,rev,to);
		}
	}

	while(q--) {
		int s,t;
		cin>>s>>t;
		if(s/k/S == t/k/S) {
			cout<<solve(s,t,k)<<nl;
		} else {
			int mid = t/k/S*S*k;
			int ans = INF;
			for(int j=0;j<k;j++) {
				ans = min(ans, to[mid+j][s]+fr[mid+j][t]);
			}
			if(ans==INF) cout<<-1<<nl;
			else cout<<ans<<nl;
		}
	}

	return 0;
}
