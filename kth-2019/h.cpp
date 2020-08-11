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

namespace SAT {
	const int N = 8e5+1;
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
	////////////////////////////////////////////////////////////////////////////////
	// 2-SAT using SCC (previous version was TESTED F - SouthAmerica03)
	////////////////////////////////////////////////////////////////////////////////
	bool truth[N/2]; // N must be at least 2 times the number of variables
	// the clause a || b becomes !a => b and !b => a in the implication graph
	void add_clause(int a, int b) { adj[a].push_back(b); }
	bool two_sat(int n) { get_scc(n);
		for (int i = 0; i < n; i += 2) { if (scomp[i] == scomp[i^1]) return false;
			truth[i/2] = (scomp[i] < scomp[i^1]); } return true;
	}
}

int ZERO(int x) {
	return (4*x+0)*2;
}
int HALF(int x) {
	return (4*x+1)*2;
}
int ONE(int x) {
	return (4*x+2)*2;
}
int TWO(int x) {
	return (4*x+3)*2;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);

	int n,m;
	cin>>n>>m;
	for(int i=0;i<m;i++) {
		int a,b; char c;
		cin>>a>>b>>c;
		--a; --b;
		if(c=='x') {
			SAT::add_clause(ZERO(a)^1, ZERO(b));
			SAT::add_clause(ZERO(b)^1, ZERO(a));
		} else if(c=='-') {
			SAT::add_clause(ZERO(a), ZERO(a)^1);
			SAT::add_clause(ZERO(b), ZERO(b)^1);
			SAT::add_clause(TWO(a), TWO(a)^1);
			SAT::add_clause(TWO(b), TWO(b)^1);
			SAT::add_clause(ONE(a), HALF(b));
			SAT::add_clause(ONE(b), HALF(a));
			SAT::add_clause(HALF(a)^1, ONE(b)^1);
			SAT::add_clause(HALF(b)^1, ONE(a)^1);
		} else if(c=='=') {
			SAT::add_clause(ZERO(a), ZERO(a)^1);
			SAT::add_clause(ZERO(b), ZERO(b)^1);
			SAT::add_clause(ONE(a), ONE(b));
			SAT::add_clause(ONE(b), ONE(a));
			SAT::add_clause(ONE(a)^1, ONE(b)^1);
			SAT::add_clause(ONE(b)^1, ONE(a)^1);
			SAT::add_clause(HALF(a), TWO(b));
			SAT::add_clause(HALF(b), TWO(a));
			SAT::add_clause(HALF(a)^1, TWO(b)^1);
			SAT::add_clause(HALF(b)^1, TWO(a)^1);
			SAT::add_clause(TWO(a), HALF(b));
			SAT::add_clause(TWO(b), HALF(a));
			SAT::add_clause(TWO(a)^1, HALF(b)^1);
			SAT::add_clause(TWO(b)^1, HALF(a)^1);
		} else {
			SAT::add_clause(ZERO(a), ZERO(a)^1);
			SAT::add_clause(ZERO(b), ZERO(b)^1);
			SAT::add_clause(HALF(a), HALF(a)^1);
			SAT::add_clause(HALF(b), HALF(b)^1);
			SAT::add_clause(ONE(a), TWO(b));
			SAT::add_clause(ONE(b), TWO(a));
			SAT::add_clause(TWO(a)^1, ONE(b)^1);
			SAT::add_clause(TWO(b)^1, ONE(a)^1);
		}
	}
	for(int i=0;i<n;i++) {
		for(int j=0;j<4;j++) {
			for(int k=0;k<4;k++) {
				if(j==k) continue;
				SAT::add_clause((4*i+j)*2, ((4*i+k)*2)^1);
			}
		}
	}

	SAT::get_scc(2*4*n);
	assert(SAT::two_sat(2*4*n));
	for(int i=0;i<n;i++) {
		if(SAT::truth[4*i]) {
			cout<<'x';
		} else if(SAT::truth[4*i+1]) {
			cout<<'-';
		} else if(SAT::truth[4*i+2]) {
			cout<<'=';
		} else {
			if(SAT::truth[4*i+3]) cout<<'+';
			cout<<'?';
			//assert(SAT::truth[4*i+3]);
			//cout<<'+';
		}
	}
	cout<<nl;

	return 0;
}
