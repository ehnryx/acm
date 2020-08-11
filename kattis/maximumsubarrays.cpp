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



int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);

	int n,k;
	cin>>n>>k;
	int a[n+1];
	for(int i=1;i<=n;i++) {
		cin>>a[i];
	}

	ll dp[n+1][k+1][2];
	fill(&dp[0][0][0],&dp[0][0][0]+(n+1)*(k+1)*2,-INFLL);
	dp[0][0][0] = 0;
	for(int i=1;i<=n;i++) {
		for(int j=0;j<=k;j++) {
			if(j>0) dp[i][j][1] = dp[i-1][j-1][0]+a[i];
			dp[i][j][1] = max(dp[i][j][1],dp[i-1][j][1]+a[i]);
			dp[i][j][0] = max(dp[i-1][j][0],dp[i][j][1]);
		}
	}
	cout<<dp[n][k][0]<<nl;

	return 0;
}
