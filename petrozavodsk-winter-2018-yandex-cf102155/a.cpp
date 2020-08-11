#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

#define For(i,n) for (int i=0; i<n; i++)
#define FOR(i,a,b) for (int i=a; i<=b; i++)
#define Down(i,n) for (int i=n-1; i>=0; i--)
#define DOWN(i,a,b) for (int i=b; i>=a; i--)

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
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



//#define FILEIO
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);
#ifdef FILEIO
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#endif

	int n, s;
	cin >> n >> s;
	int m = 2*n*(s+1);

	int order[m+1];
	FOR(i,1,m) {
		cin >> order[i];
	}

	int ps;
	cin >> ps;
	int standard[ps];
	For(i,ps) {
		cin >> standard[i];
	}
	sort(standard, standard+ps, greater<int>());

	int pu;
	cin >> pu;
	int ultimate[pu];
	For(i,pu) {
		cin >> ultimate[i];
	}
	sort(ultimate, ultimate+pu, greater<int>());

	ps = 2*n*s;
	pu = 2*n;

	int dp[m+1][ps+1][pu+1][1<<(2*n)];
	memset(dp, INF, sizeof dp);
	dp[0][0][0][0] = 0;
	FOR(i,1,m) {
		int cur = order[m-i+1]-1;
		FOR(j,0,ps) {
			FOR(k,0,pu) {
				For(bm,1<<(2*n)) {
					if (cur<n) dp[i][j][k][bm] = -INF;
					else dp[i][j][k][bm] = INF;
					// take standard
					if (j>0 && abs(dp[i-1][j-1][k][bm]) != INF) {
						if (cur<n) dp[i][j][k][bm] = max(dp[i][j][k][bm], dp[i-1][j-1][k][bm] + standard[ps-j]);
						else dp[i][j][k][bm] = min(dp[i][j][k][bm], dp[i-1][j-1][k][bm] - standard[ps-j]);
					}
					// take ultimate
					if (k>0 && abs(dp[i-1][j][k-1][bm^1<<cur]) != INF) {
						if (cur<n) dp[i][j][k][bm] = max(dp[i][j][k][bm], dp[i-1][j][k-1][bm^1<<cur] + ultimate[pu-k]);
						else dp[i][j][k][bm] = min(dp[i][j][k][bm], dp[i-1][j][k-1][bm^1<<cur] - ultimate[pu-k]);
					}
					//if (abs(dp[i][j][k][bm]) != INF) cerr << i << " " << j << " " << k << " " << bitset<4>(bm) << " -> " << dp[i][j][k][bm] << nl;
				}
			}
		}
	}
	//cerr << "query ans " << m << " " << ps << " " << pu << " " << (1<<(2*n))-1 << nl;
	cout << dp[m][ps][pu][(1<<(2*n))-1] << nl;

	return 0;
}
