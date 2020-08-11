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

const int N = 250;
ll dp[N][N][N][3];
ll cnt[3];

inline ll nc2(ll n) {
	return n*(n-1)/2;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	freopen("khoshaf.in", "r", stdin);

	int T;
	cin>>T;
	while(T--) {
		int n,K,l,r;
		cin>>n>>K>>l>>r;
		for(int i=0;i<3;i++) {
			cnt[i] = (r + 3-i)/3 - (l-1 + 3-i)/3;
			//cerr<<"cnt "<<i<<" : "<<cnt[i]<<nl;
		}
		if(n>=N-1) {
			cout<<0<<nl;
			continue;
		}

		for(int t=0;t<3;t++) {
			dp[0][0][0][t] = 0;
			dp[0][1][0][t] = 0;
			dp[0][0][1][t] = 0;
		}
		dp[0][1][0][0] = 1;
		for(int i=1;i<=n;i++) {
			for(int j=0;j<=i+1;j++) {
				for(int k=0;k+j<=i+1;k++) {
					if(j>0) {
						dp[i][j][k][0] = 0;
						for(int t=0;t<3;t++) {
							dp[i][j][k][0] += dp[i-1][j-1][k][t] * cnt[(3-t)%3];
						}
						dp[i][j][k][0] %= MOD;
					}
					if(k>0) {
						dp[i][j][k][1] = 0;
						for(int t=0;t<3;t++) {
							dp[i][j][k][1] += dp[i-1][j][k-1][t] * cnt[(4-t)%3];
						}
						dp[i][j][k][1] %= MOD;
					}
					if(j+k<=i) {
						dp[i][j][k][2] = 0;
						for(int t=0;t<3;t++) {
							dp[i][j][k][2] += dp[i-1][j][k][t] * cnt[(5-t)%3];
						}
						dp[i][j][k][2] %= MOD;
					}
				}
			}
		}

		ll ans = 0;
		for(int j=0;j<=n+1;j++) {
			for(int k=0;k+j<=n+1;k++) {
				int i = n+1-j-k;
				//cerr<<"@ "<<i<<" "<<j<<" "<<k<<nl;
				if(nc2(i)+nc2(j)+nc2(k)==K) {
					//cerr<<"  good"<<nl;
					for(int t=0;t<3;t++) {
						ans += dp[n][j][k][t];
						//cerr<<"add "<<dp[n][j][k][t]<<nl;
					}
				}
			}
		}
		cout<<ans%MOD<<nl;
	}

	return 0;
}
