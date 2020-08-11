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

const int N = 15;
int adj[N][N];
ll good[N+1][N+1][1<<N], match[N+1][N+1][1<<N];
vector<int> bms[N+1];

int solve() {
	int n;
	cin >> n;
	For(i,n) {
		For(j,n) {
			cin >> adj[i][j];
		}
	}

	FOR(i,1,n) {
		bms[i].clear();
	}
	For(bm,1<<n) {
		if (bm > 0) {
			bms[__builtin_popcount(bm)].push_back(bm);
		}
	}

	memset(good, 0, sizeof good);
	memset(match, 0, sizeof match);
	good[0][0][0] = match[0][0][0] = 1;

	For(i,n) {
		For(j,n) {
			for (int bm : bms[i+1]) {
				if (bm&1<<j) {
					For(k,n+1) {
						if (adj[i][j] == 2) {
							if (k > 0) {
								match[i+1][k][bm] += match[i][k-1][bm^1<<j];
								good[i+1][k][bm] += good[i][k-1][bm^1<<j];
							}
						} else {
							match[i+1][k][bm] += match[i][k][bm^1<<j];
							if (adj[i][j] == 1) {
								good[i+1][k][bm] += good[i][k][bm^1<<j];
							}
						}
					}
				}
			}
		}
	}

	ll ans = good[n][0][(1<<n)-1];
	FOR(k,1,n) {
		ans += match[n][k][(1<<n)-1];
	}
	cout << ans << nl;

	return 0;
}

//#define FILEIO
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);
#ifdef FILEIO
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#endif

	int T;
	cin >> T;
	while (T--) {
		assert(solve() == 0);
	}

	return 0;
}
