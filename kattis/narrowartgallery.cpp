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

	int n,m;
	cin>>n>>m;
	int a[n+2][2];
	for(int i=1;i<=n+1;i++) {
		cin>>a[i][0]>>a[i][1];
	}

	int dp[n+2][4][m+1];
	fill(&dp[0][0][0],&dp[0][0][0]+(n+2)*4*(m+1),-INF);
	dp[0][0b11][0] = 0;
	for(int i=1;i<=n+1;i++) {
		for(int j=0;j<=m;j++) {
			for(int bm=0;bm<4;bm++) {
				int cnt = 2-__builtin_popcount(bm);
				if(j-cnt<0) continue;
				for(int pm=0;pm<4;pm++) {
					if(bm&pm) {
						int cost = 0;
						if(bm&1) cost += a[i][0];
						if(bm&2) cost += a[i][1];
						dp[i][bm][j] = max(dp[i][bm][j], dp[i-1][pm][j-cnt] + cost);
					}
				}
			}
		}
	}
	cout<<dp[n+1][0b11][m]<<nl;

	return 0;
}
