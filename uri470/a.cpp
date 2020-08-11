#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

// DON'T USE THESE MACROS DURING ICPC PRACTICE
#define For(i,n) for (int i=0; i<n; i++)
#define FOR(i,a,b) for (int i=a; i<=b; i++)
#define Down(i,n) for (int i=n-1; i>=0; i--)
#define DOWN(i,a,b) for (int i=b; i>=a; i--)

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef pair<ld,ld> pdd;
typedef complex<ld> pt;
typedef vector<pt> pol;
typedef vector<int> vi;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

int sqr(int x) { return x*x; }

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);

	int m,n,k;
	cin>>m>>n>>k;
	int a[k],b[k],r[k];
	for(int i=0;i<k;i++) {
		cin>>a[i]>>b[i]>>r[i];
	}

	vector<int> adj[n+2];
	for(int i=0;i<k;i++) {
		for(int j=0;j<i;j++) {
			if(sqr(a[i]-a[j])+sqr(b[i]-b[j])<=sqr(r[i]+r[j])) {
				adj[i].push_back(j);
				adj[j].push_back(i);
			}
		}
		if(abs(a[i]-0)<=r[i] || abs(b[i]-n)<=r[i]) {
			adj[n].push_back(i);
		}
		if(abs(a[i]-m)<=r[i] || abs(b[i]-0)<=r[i]) {
			adj[i].push_back(n+1);
		}
	}

	vector<int> vis(n+2,0);
	stack<int> bfs;
	bfs.push(n);
	vis[n] = 1;
	while(!bfs.empty()) {
		int u = bfs.top(); bfs.pop();
		for(int v:adj[u]) {
			if(!vis[v]) {
				vis[v] = 1;
				bfs.push(v);
			}
		}
	}
	if(!vis[n+1]) {
		cout<<"S"<<nl;
	} else {
		cout<<"N"<<nl;
	}

	return 0;
}
