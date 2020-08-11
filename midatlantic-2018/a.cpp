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

const int N = 2e3+1;
namespace SAT {
	int low[N],vis[N],scomp[N],scompNum,I;
	vector<int> adj[N]; stack<int> verts;
	void scc(int u) { low[u] = vis[u] = ++I; verts.push(u);
		for (int v : adj[u]) {
			if (!vis[v]) scc(v);
			if (scomp[v] == -1) low[u] = min(low[u], low[v]); }
		if (vis[u] <= low[u]) { int v;
			do { v=verts.top(); verts.pop(); scomp[v]=scompNum; } while (v != u);
			++scompNum; }}
	void get_scc(int n) { memset(vis,0,sizeof vis); memset(scomp,-1,sizeof scomp);
		scompNum=I=0; for (int i=0; i<n; ++i) if (!vis[i]) scc(i); }
	bool truth[N/2]; // N must be at least 2 times the number of variables
	// the clause a || b becomes !a => b and !b => a in the implication graph
	void add_edge(int a, int b) { adj[a].push_back(b); }
	bool two_sat(int n) { get_scc(n);
		for (int i = 0; i < n; i += 2) { if (scomp[i] == scomp[i^1]) return false;
			truth[i/2] = (scomp[i] < scomp[i^1]); } return true; }
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);

	int n;
	cin>>n;
	int x[n],y[n];
	for(int i=0;i<n;i++) {
		cin>>x[i]>>y[i];
	}

	auto valid = [&](int ub) {
		for(int i=0;i<2*n;i++) {
			SAT::adj[i].clear();
		}
		for(int i=0;i<n;i++) {
			for(int j=0;j<i;j++) {
				if(abs(x[i]-x[j])+abs(y[i]-y[j]) > ub) {
					SAT::add_edge(i<<1, j<<1|1);
					SAT::add_edge(j<<1, i<<1|1);
					SAT::add_edge(i<<1|1, j<<1);
					SAT::add_edge(j<<1|1, i<<1);
				}
			}
		}
		return SAT::two_sat(2*n);
	};

	int l = 0;
	int r = 2000;
	while(l<r) {
		int m = (l+r)/2;
		if(valid(m)) {
			r = m;
		} else {
			l = m+1;
		}
	}
	cout<<l<<nl;

	return 0;
}
