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

	int n,w,h;
	cin>>n>>w>>h;

	int dp[w+1][n+1];
	memset(dp,0,sizeof dp);
	dp[0][0] = 1;
	for(int i=1;i<=w;i++) {
		for(int j=0;j<=n;j++) {
			for(int k=0;k<=h&&j-k>=0;k++) {
				dp[i][j] = (dp[i][j] + dp[i-1][j-k]) % MOD;
			}
		}
	}

	ll ans = 0;
	for(int j=0;j<=n;j++) {
		ans += dp[w][j];
	}
	for(int i=0;i<=h;i++) {
		if(w*i <= n) ans--;
	}
	cout<<(ans+MOD)%MOD<<nl;

	return 0;
}
