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
const char INF = 100;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int N = 25;
int a[N];
char dp[1<<N][3];
int n,m; string s;
char solve(int i, int bm, int done) {
	if(dp[bm][done]!=-1) return dp[bm][done];
	if(i==m) return dp[bm][done]=(done?INF:0);
	if(s[i]=='0') return dp[bm][done]=0;
	{
		int c=s[i]-'0';
		for(int j=lower_bound(a,a+n,c)-a;j<n&&a[j]==c;j++) {
			if(bm&1<<j) continue;
			int r=solve(i+1,bm|1<<j,done);
			if(r) return r;
		}
	}
	if(i+1<m) {
		int c=10*(s[i]-'0')+s[i+1]-'0';
		for(int j=lower_bound(a,a+n,c)-a;j<n&&a[j]==c;j++) {
			if(bm&1<<j) continue;
			int r=solve(i+2,bm|1<<j,done);
			if(r) return r;
		}
	}
	if(!done) {
		if(solve(i+1,bm,1)) return s[i]-'0';
		if(i+1<m&&solve(i+2,bm,2)) return 10*(s[i]-'0')+s[i+1]-'0';
	}
	return dp[bm][done]=0;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);

	cin>>s;
	m = s.size();
	cin>>n;
	for(int i=0;i<n;i++) {
		cin>>a[i];
	}
	sort(a,a+n);
	memset(dp,-1,sizeof dp);
	cout<<!!solve(0,0,0)<<nl;

	return 0;
}
