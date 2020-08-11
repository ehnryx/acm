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

const int N = 16;
int dp[1<<N];
int solve(int bm) {
	if (dp[bm] != -1) return dp[bm];
	dp[bm] = 0;
	for (int i=0; i<N; i++) {
		if (!(bm&1<<i)) continue;
		dp[bm] |= !solve(bm^1<<i);
		for (int j=0; j<i; j++) {
			dp[bm] |= !solve(bm^1<<i^1<<j);
			for (int k=0; k<j; k++) {
				dp[bm] |= !solve(bm^1<<i^1<<j^1<<k);
			}
		}
	}
	return dp[bm];
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);

	memset(dp, -1, sizeof dp);
	for (int bm=0; bm<1<<N; bm++) {
		int val = 0;
		for (int i=0; i<N; i++) {
			if (bm&1<<i) {
				val += i+1;
			}
		}
		cout << bitset<N>(bm) << " -> " << solve(bm) << endl;
	}

	return 0;
}
