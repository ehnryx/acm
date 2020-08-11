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
	int i, d;
	Edge(int _i, int _d=0): i(_i), d(_d) {}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);

	int n,m;
	cin>>n>>m;
	string g[n];
	for(int i=0;i<n;i++) {
		cin>>g[i];
	}

	auto get = [&](int i, int j, int k) {
		return (i*m + j)*2 + k;
	};

	int t = n*m*2;
	vector<Edge> adj[n*m*2+1];
	for(int i=0;i<n;i++) {
		for(int j=0;j<m;j++) {
			if(g[i][j]!='#') {
				if(i>0) adj[get(i,j,0)].push_back(Edge(get(i-1,j,1)));
				if(j>0) adj[get(i,j,0)].push_back(Edge(get(i,j-1,1)));
				if(i+1<n) adj[get(i,j,0)].push_back(Edge(get(i+1,j,1)));
				if(j+1<m) adj[get(i,j,0)].push_back(Edge(get(i,j+1,1)));
				if(g[i][j]=='c') {
					adj[get(i,j,1)].push_back(Edge(get(i,j,0), 1));
				} else if(g[i][j]=='D') {
					adj[get(i,j,1)].push_back(Edge(get(i,j,0)));
					if(i==0 || j==0 || i==n-1 || j==m-1) {
						adj[get(i,j,0)].push_back(Edge(t));
					}
				}
			}
		}
	}

	int a,b;
	cin>>a>>b;
	--a; --b;
	vector<int> dist(n*m*2+1, -1);
	deque<Edge> bfs;
	bfs.push_back(Edge(get(a,b,1)));
	dist[get(a,b,1)] = 0;
	while(!bfs.empty()) {
		Edge cur = bfs.front();
		bfs.pop_front();
		if(cur.i==t) {
			cout<<cur.d<<nl;
			return 0;
		}
		for(Edge e:adj[cur.i]) {
			if(dist[e.i]==-1) {
				dist[e.i] = cur.d + e.d;
				if(e.d==0) bfs.push_front(Edge(e.i, dist[e.i]));
				else bfs.push_back(Edge(e.i, dist[e.i]));
			}
		}
	}
	assert(false);

	return 0;
}
