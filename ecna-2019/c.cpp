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
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int MAXN = 52;
const int MAXM = 52;
const ld INF = 1e9;
const ld EPS = 1e-11;

namespace LP {
	void pivot(int m,int n,ld a[MAXM][MAXN],
			int B[MAXM],int N[MAXN],int r,int c) {
		int i,j; swap(N[c], B[r]); a[r][c]=1/a[r][c];
		for(j=0;j<=n;j++) if(j!=c) a[r][j]*=a[r][c];
		for(i=0;i<=m;i++) if(i!=r) {
			for(j=0;j<=n;j++) if(j!=c) a[i][j]-=a[i][c]*a[r][j];
			a[i][c] = -a[i][c]*a[r][c]; } }
	int feasible(int m,int n,ld a[MAXM][MAXN],int B[MAXM],int N[MAXN]) {
		int r,c,i; ld p,v;
		while(1) {
			for(p=INF,i=0; i<m; i++) if(a[i][n]<p) p=a[r=i][n];
			if(p>-EPS) return 1;
			for(p=0,i=0; i<n; i++) if(a[r][i]<p) p=a[r][c=i];
			if(p>-EPS) return 0;
			p = a[r][n]/a[r][c];
			for(i=r+1; i<m; i++) if(a[i][c]>EPS) {
				v = a[i][n]/a[i][c];
				if(v<p) r=i,p=v; }
			pivot(m,n,a,B,N,r,c); } }
	int simplex(int m,int n,ld a[MAXM][MAXN],ld b[MAXN],ld& ret) {
		int B[MAXM],N[MAXN],r,c,i; ld p,v;
		for(i=0; i<n; i++) N[i]=i;
		for(i=0; i<m; i++) B[i]=n+i;
		if(!feasible(m,n,a,B,N)) return 0;
		while(1) {
			for(p=0,i=0; i<n; i++) if(a[m][i]>p) p=a[m][c=i];
			if(p<EPS) {
				for(i=0; i<n; i++) if(N[i]<n) b[N[i]]=0;
				for(i=0; i<m; i++) if(B[i]<n) b[B[i]]=a[i][n];
				ret = -a[m][n];
				return 1; }
			for(p=INF,i=0; i<m; i++) if(a[i][c]>EPS) {
				v = a[i][n]/a[i][c];
				if(v<p) p=v,r=i; }
			if(p==INF) return -1;
			pivot(m,n,a,B,N,r,c); } }
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(2);

	ld a[MAXM][MAXN];
	int n,m;
	cin>>n>>m;
	for(int i=0;i<n;i++) {
		cin>>a[i][m];
	}
	for(int i=0;i<m;i++) {
		for(int j=0;j<n;j++) {
			cin>>a[j][i];
		}
		cin>>a[n][i];
	}

	ld b[MAXN];
	ld ans = 0;
	assert(LP::simplex(n,m,a,b,ans));
	cout<<ans*100<<nl;

	return 0;
}
