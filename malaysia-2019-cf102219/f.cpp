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
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int N = 2e3+1;
const int M = 1<<9;
ll dp[N][M];
unordered_set<int> bad[N];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);

	int n, e, k;
	cin >> n >> e >> k;

	for (int i=0; i<k; i++) {
		int a, b;
		cin >> a >> b;
		bad[a].insert(b);
	}

	dp[0][0] = 1;
	for (int i=1; i<=n; i++) {
		for (int bm=0; bm<M; bm++) {
			for (int j=0; j<=2*e; j++) {
				int id = i-e+j;
				if (id<=0 || id>n) continue;
				if (!(bm>>1&1<<j) && !bad[i].count(i-e+j)) {
					dp[i][bm>>1^1<<j] = (dp[i][bm>>1^1<<j] + dp[i-1][bm]) % MOD;
				}
			}
		}
	}
	ll ans = 0;
	for (int bm=0; bm<M; bm++) {
		ans += dp[n][bm];
	}
	cout << ans % MOD << nl;

	return 0;
}
