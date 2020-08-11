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

const int N = 1e3+1;
vector<int> adj[N];
int sz[N], par[N];

int preproc(int u, int p) {
	par[u] = p;
	sz[u] = 1;
	for(int v:adj[u]) {
		if(v==p) continue;
		sz[u] += preproc(v,u);
	}
	return sz[u];
}

ld x[N], y[N];
void solve(int u, ld s, ld t) {
	ld cur = s;
	for(int v:adj[u]) {
		if(v==par[u]) continue;
		ld len = (ld)sz[v]/(sz[u]-1) * (t-s);
		ld ang = (cur+cur+len)/2;
		x[v] = x[u] + cos(ang);
		y[v] = y[u] + sin(ang);
		solve(v, cur, cur+len);
		cur += len;
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);

	int n;
	cin>>n;
	for(int i=1;i<n;i++) {
		int a,b;
		cin>>a>>b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	preproc(1,0);

	x[1] = y[1] = 0;
	solve(1, -M_PI, M_PI);
	for(int i=1;i<=n;i++) {
		cout<<x[i]<<" "<<y[i]<<nl;
	}

	return 0;
}
