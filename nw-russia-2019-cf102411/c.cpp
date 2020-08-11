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

const int N = 101;
unordered_multiset<int> adj[N*N];
int x[N*N], y[N*N];

list<int> ans;
void euler(int u, list<int>::iterator it) {
	for(auto jt=adj[u].begin(); jt!=adj[u].end(); ) {
		int v = *jt; adj[u].erase(jt);
		euler(v, ans.insert(it, v));
		jt = adj[u].begin();
	}
}

int add_edges(int i, int j) {
	int a = i*N + j;
	int b = (i+1)*N + j;
	x[a] = i; y[a] = j;
	x[b] = i+1; y[b] = j;
	x[a+1] = i; y[a+1] = j+1;
	x[b+1] = i+1; y[b+1] = j+1;
	if(i%2 == 0) {
		adj[a].insert(b+1);
		adj[a+1].insert(b);
		adj[b].insert(a);
		adj[b+1].insert(a+1);
		return b;
	} else {
		adj[a].insert(b);
		adj[a+1].insert(b+1);
		adj[b].insert(a+1);
		adj[b+1].insert(a);
		return a;
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	int n,m;
	cin>>m>>n;

	string g[n];
	int s = -1;
	for(int i=0;i<n;i++) {
		cin>>g[i];
		for(int j=0;j<m;j++) {
			if(g[i][j] == 'X') {
				s = add_edges(i,j);
			}
		}
	}

	if(s == -1) {
		cout<<0<<nl;
	} else {
		euler(s, ans.begin());
		cout<<ans.size()-1<<nl;
		for(int it:ans) {
			cout<<y[it]<<" "<<x[it]<<nl;
		}
	}

	return 0;
}
