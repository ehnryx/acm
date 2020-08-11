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

const int N = 1e5+1;
vector<pii> adj[N];
vector<int> rev[N];
int vis[N];

void traverse(int u) {
	vis[u] = true;
	for(int v:rev[u]) {
		if(!vis[v]) {
			traverse(v);
		}
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);

	int n,m,s,t;
	cin>>n>>m>>s>>t;

	for(int i=0;i<m;i++) {
		int a,b,c;
		cin>>a>>b>>c;
		adj[a].push_back({c,b});
		rev[b].push_back(a);
	}
	traverse(t);
	if(!vis[s]) {
		cout<<"IMPOSSIBLE"<<nl;
		return 0;
	}

	vector<int> ans;
	unordered_set<int> seen;
	for(int u=s;u!=t;) {
		pii cur(INF,INF);
		for(pii e:adj[u]) {
			if(vis[e.second]) {
				cur = min(cur,e);
			}
		}
		if(cur.first==INF) {
			cout<<"IMPOSSIBLE"<<nl;
			return 0;
		}
		if(seen.count(cur.first)) {
			cout<<"TOO LONG"<<nl;
			return 0;
		}
		ans.push_back(cur.first);
		seen.insert(cur.first);
		u = cur.second;
	}
	for(int it:ans) {
		cout<<it<<" ";
	}
	cout<<nl;

	return 0;
}
