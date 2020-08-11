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

const int N = 1e3+1;
const int M = 1e4+1;
int v[N], p[N];
int dp[N][M];

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(10);

	int n, a, b;
	cin >> n >> a >> b;
	if(a > b) swap(a,b);
	for(int i=1; i<=n; i++) {
		cin >> v[i];
		p[i] = p[i-1] + v[i];
	}

	dp[0][0] = true;
	for(int i=1; i<=n; i++) {
		bool ok = false;
		for(int t=0; t<=min(a,p[i]); t++) {
			if(p[i]-t > b) continue;
			if(dp[i-1][t]) {
				dp[i][t] = true;
			}
			if(t >= v[i]) {
				if(dp[i-1][t-v[i]]) {
					dp[i][t] = true;
				}
			}
			if(dp[i][t]) {
				ok = true;
			}
		}
		if(!ok) {
			cout << i-1 << nl;
			return 0;
		}
	}
	cout << n << nl;

	return 0;
}
