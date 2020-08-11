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

vector<int> di = {1,-1,0,0};
vector<int> dj = {0,0,1,-1};

const int N = 100+2;
char g[N][N],h[N][N];

void explore(int i, int j, char c) {
	g[i][j] = c;
	for(int d=0;d<4;d++) {
		int ni = i + di[d];
		int nj = j + dj[d];
		if(g[ni][nj]=='X') {
			explore(ni,nj,c);
		}
	}
}

void flood(char a[N][N], int i, int j, char c) {
	a[i][j] = 'x';
	for(int d=0;d<4;d++) {
		int ni = i + di[d];
		int nj = j + dj[d];
		if(a[ni][nj] && a[ni][nj]!=c && a[ni][nj]!='x') {
			flood(a,ni,nj,c);
		}
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);

	int n,m;
	cin>>n>>m;
	int ai,aj,bi,bj;
	ai=aj=bi=bj=0;
	for(int i=1;i<=n;i++) {
		for(int j=1;j<=m;j++) {
			cin>>g[i][j];
			if(g[i][j]=='A') {
				ai=i; aj=j;
			}
			if(g[i][j]=='B') {
				bi=i; bj=j;
			}
		}
	}
	assert(ai);
	assert(aj);
	assert(bi);
	assert(bj);

	for(int i=1;i<=n;i++) {
		for(int j=1;j<=m;j++) {
			if(g[i][j]=='X' && g[i-1][j]!='.' && g[i+1][j]!='.'
					&& g[i][j-1]!='.' && g[i][j+1]!='.'
					&& g[i-1][j-1]=='.' && g[i-1][j+1]=='.'
					&& g[i+1][j-1]=='.' && g[i+1][j+1]=='.') {
				g[i][j] = 'x';
			}
		}
	}

	explore(ai,aj,'A');
	explore(bi,bj,'B');
	for(int i=1;i<=n;i++) {
		for(int j=1;j<=m;j++) {
			if(g[i][j]=='x') {
				if(g[i-1][j]=='X') {
					explore(i-1,j,g[i+1][j]);
				} else {
					explore(i+1,j,g[i-1][j]);
				}
				if(g[i][j-1]=='X') {
					explore(i,j-1,g[i][j+1]);
				} else {
					explore(i,j+1,g[i][j-1]);
				}
			}
		}
	}

	for(int i=1;i<=n;i++) {
		for(int j=1;j<=m;j++) {
			h[i][j] = g[i][j];
			cerr<<g[i][j];
		}
		cerr<<nl;
	}
	cerr<<nl;

	for(int i=1;i<=n;i++) {
		if(g[i][1] != 'A') flood(g,i,1,'A');
		if(g[i][m] != 'A') flood(g,i,m,'A');
	}
	for(int j=1;j<=m;j++) {
		if(g[1][j] != 'A') flood(g,1,j,'A');
		if(g[n][j] != 'A') flood(g,n,j,'A');
	}

	for(int i=1;i<=n;i++) {
		if(h[i][1] != 'B') flood(h,i,1,'B');
		if(h[i][m] != 'B') flood(h,i,m,'B');
	}
	for(int j=1;j<=m;j++) {
		if(h[1][j] != 'B') flood(h,1,j,'B');
		if(h[n][j] != 'B') flood(h,n,j,'B');
	}

	int ac, ab, bc;
	ac = ab = bc = 0;
	for(int i=1;i<=n;i++) {
		for(int j=1;j<=m;j++) {
			if(g[i][j]=='.') ac++;
			if(h[i][j]=='.') bc++;
			if(g[i][j]=='.' && h[i][j]=='.') ab++;
			cerr<<g[i][j];
		}
		cerr<<nl;
	}
	cerr<<nl;

	cout<<ac-ab<<" "<<bc-ab<<" "<<ab<<nl;

	return 0;
}
