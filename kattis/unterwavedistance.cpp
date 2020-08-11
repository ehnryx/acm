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

ll cube(ll x) { return x*x*x; }

const int N = 5e4+1;
int root[N];
int find(int i) {
	if(root[i]==-1) return i;
	return root[i]=find(root[i]);
}
void link(int i, int j) {
	if(find(i)==find(j)) return;
	root[find(i)]=find(j);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);

	memset(root,-1,sizeof root);

	int n;
	cin>>n;
	ll g[n]; char t[n];
	vector<pair<ll,int>> p;
	for(int i=1;i<=n;i++) {
		cin>>g[i]>>t[i];
		p.push_back(make_pair(g[i],i));
	}
	sort(p.begin(),p.end());

	int m;
	cin>>m;
	set<int> adj[n+1];
	for(int i=0;i<m;i++) {
		int a,b;
		cin>>a>>b;
		adj[a].insert(b);
		adj[b].insert(a);
		link(a,b);
	}

	auto notinc = [&](int a, int b) {
		for(int i:adj[a]) {
			if(i!=b && !adj[b].count(i)) {
				return true;
			}
		}
		return false;
	};

	auto calc = [&](int a, int b) {
		ll res = INFLL;
		if(t[a]==t[b]||find(a)!=find(b)) return res;
		res = abs(cube(g[a])-cube(g[b]));
		if(!adj[a].count(b)) {
			res = min(res, abs(cube(g[a]-1)-cube(g[b])));
			res = min(res, abs(cube(g[a])-cube(g[b]-1)));
		} else {
			res = min(res, abs(cube(g[a]-1)-cube(g[b]+1)));
			res = min(res, abs(cube(g[a]+1)-cube(g[b]-1)));
			if(notinc(a,b)) res = min(res, abs(cube(g[a]+1)-cube(g[b])));
			if(notinc(b,a)) res = min(res, abs(cube(g[a])-cube(g[b]+1)));
		}
		return res;
	};

	ll ans = INFLL;
	for(int i=0;i<n;i++) {
		int u = p[i].second;
		for(int v:adj[u]) {
			ans = min(ans,calc(u,v));
		}
		for(int j=1;j<=21;j++) {
			if(i-j>=0) ans = min(ans,calc(u,p[i-j].second));
			if(i+j<n) ans = min(ans,calc(u,p[i+j].second));
		}
	}
	cout<<ans<<nl;

	return 0;
}
