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

enum {
	TOP,
	BOT,
	LEFT,
	RIGHT,
	UP,
	DOWN,
};
const int mask = (1<<5)-1;

const int N = 100;
int g[N][N];
unordered_set<int> vis[N][N];

void swapv(int& bm, int i, int j) {
	int u = mask&bm>>(5*i);
	int v = mask&bm>>(5*j);
	bm ^= (u^v)<<(5*i) ^ (u^v)<<(5*j);
}

int n,m;
bool solve(int i, int j, int bm) {
	if((bm&mask)!=g[i][j] && (bm&mask)!=mask) return false;
	if(i==n-1 && j==m-1) return true;
	if(vis[i][j].count(bm)) return false;
	vis[i][j].insert(bm);
	if((bm&mask) == mask) bm ^= mask ^ g[i][j];
	vis[i][j].insert(bm);
	if(i>0) {
		// top -> up -> bot -> down
		int sm = bm;
		swapv(sm,BOT,DOWN);
		swapv(sm,UP,BOT);
		swapv(sm,TOP,UP);
		if(solve(i-1,j,sm)) return true;
	}
	if(j>0) {
		// top -> left -> bot -> right
		int sm = bm;
		swapv(sm,BOT,RIGHT);
		swapv(sm,LEFT,BOT);
		swapv(sm,TOP,LEFT);
		if(solve(i,j-1,sm)) return true;
	}
	if(i+1<n) {
		// top -> down -> bot -> up
		int sm = bm;
		swapv(sm,BOT,UP);
		swapv(sm,DOWN,BOT);
		swapv(sm,TOP,DOWN);
		if(solve(i+1,j,sm)) return true;
	}
	if(j+1<m) {
		// top -> right -> bot -> left
		int sm = bm;
		swapv(sm,BOT,LEFT);
		swapv(sm,RIGHT,BOT);
		swapv(sm,TOP,RIGHT);
		if(solve(i,j+1,sm)) return true;
	}
	return false;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);

	cin>>n>>m;
	for(int i=0;i<n;i++) {
		for(int j=0;j<m;j++) {
			cin>>g[i][j];
		}
	}
	if(solve(0,0,(1<<30)-1)) {
		cout<<"YES"<<nl;
	} else {
		cout<<"NO"<<nl;
	}

	return 0;
}
