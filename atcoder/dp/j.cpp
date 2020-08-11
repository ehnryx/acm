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


const int N = 300+1;
ld dp[N][N][N];
int cnt[4];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);

	int n;
	cin >> n;

	For(i,n) {
		int a;
		cin >> a;
		cnt[a]++;
	}

	dp[0][0][0] = 0;
	for (int k=0; k<=n; k++) {
		for (int j=0; j+k<=n; j++) {
			for (int i=0; i+j+k<=n; i++) {
				if (i==0 && j==0 && k==0) continue;
				dp[i][j][k] = 1;
				if (i>0) dp[i][j][k] += (ld)i/n * dp[i-1][j][k];
				if (j>0 && i+1<=n) dp[i][j][k] += (ld)j/n * dp[i+1][j-1][k];
				if (k>0 && j+1<=n) dp[i][j][k] += (ld)k/n * dp[i][j+1][k-1];
				dp[i][j][k] /= (ld)(i+j+k)/n;
			}
		}
	}
	cout << dp[cnt[1]][cnt[2]][cnt[3]] << nl;

	return 0;
}
