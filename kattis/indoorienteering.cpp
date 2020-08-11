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
const ll INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-13;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int N = 14;
ll adj[N][N];
bool vis[1<<N][N];
unordered_set<ll> seen[1<<N][N];

void collect(int bm, int u) {
	if(vis[bm][u]) return;
	vis[bm][u] = true;
	if(u==0 && bm!=1) return;
	if(__builtin_popcount(bm)==1) {
		if(bm==1 && u==0) seen[bm][u].insert(0);
		return;
	}
	for(int i=0;i<N;i++) {
		if(i==u || !(bm&1<<i)) continue;
		ll v = adj[u][i];
		collect(bm^1<<u,i);
		for(ll it:seen[bm^1<<u][i]) {
			seen[bm][u].insert(it+v);
		}
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	int n; ll m;
	cin>>n>>m;
	for(int i=0;i<n;i++) {
		for(int j=0;j<n;j++) {
			cin>>adj[i][j];
		}
	}

	for(int bm=0;bm<1<<n;bm++) {
		if(!(bm&1)) continue;
		int cnt = __builtin_popcount(bm);
		if(cnt==(n+2)/2 || cnt==(n+3)/2) {
			for(int j=1;j<n;j++) {
				if(bm&1<<j) collect(bm,j);
			}
		}
	}

	int mask = (1<<n)-1;
	for(int bm=0;bm<1<<n;bm++) {
		if(!(bm&1)) continue;
		int cnt = __builtin_popcount(bm);
		if(cnt==(n+1)/2 || cnt==(n+2)/2) {
			for(int j=1;j<n;j++) {
				if(!(bm&1<<j)) continue;
				int o = mask^bm^1^1<<j;
				for(ll it:seen[bm][j]) {
					if(seen[o][j].count(m-it)) {
						cout<<"possible"<<nl;
						return 0;
					}
				}
			}
		}
	}
	cout<<"impossible"<<nl;

	return 0;
}
