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

vector<vector<int>> adj = {
	{}, 
	// 1-6
	{ 2, 7 },
	{ 1, 3 },
	{ 2, 4, 9 },
	{ 3, 5 }, 
	{ 4, 11 },
	{ 7, 13 },
	//7-12
	{ 1, 6, 8 },
	{ 7, 9, 15 },
	{ 3, 8, 10 },
	{ 9, 11, 17 },
	{ 12, 10, 5 },
	{ 11, 19 },
	// 13-18
	{ 6, 14 },
	{ 13, 15, 20 },
	{ 14, 8, 16 },
	{ 15, 17, 22 },
	{ 10, 16, 18 },
	{ 17, 19, 24 },
	// 19-24
	{ 12, 18 },
	{ 14, 21 },
	{ 20, 22 }, 
	{ 16, 21, 23 },
	{ 22, 24 },
	{ 23, 18 }
};

int M;
vector<int> dx, dy;

const int N = 6;
int a[N], b[N];

unordered_map<ll,int> dp;
int solve(int n, ll ha, int cur) {
	if (dp.count(ha)) return dp[ha];
	vector<int> val(25,0);
	vector<int> x(n), y(n);
	For(i,n) {
		x[i] = 31&ha>>(2*5*i+5);
		y[i] = 31&ha>>(2*5*i);
		val[x[i]] = a[i];
		val[y[i]] = b[i];
	}

	int res = cur;
	For(i,n) {
		if (!x[i]) {
			For(j,M) {
				if (!val[dx[j]] && !val[dy[j]]) {
					bool bad = false;
					int add = 0;
					for (int k : adj[dx[j]]) {
						if (val[k]) {
							add++;
							if (val[k] != a[i]) {
								bad = true;
								break;
							}
						}
					}
					if (!bad) {
						for (int k : adj[dy[j]]) {
							if (val[k]) {
								add++;
								if (val[k] != b[i]) {
									bad = true;
									break;
								}
							}
						}
						if (!bad && (add || !ha)) {
							ll nxt = ha|((ll)dx[j])<<(2*5*i+5)|((ll)dy[j])<<(2*5*i);
							res = max(res, solve(n, nxt, cur + add));
							if (res == 7) return dp[ha] = res;
						}
					}
				}
			}
		}
	}
	return dp[ha] = res;
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

	FOR(i,1,24) {
		for (int j : adj[i]) {
			dx.push_back(i);
			dy.push_back(j);
		}
	}
	M = dx.size();

	for (int n; cin>>n && n; ) {
		For(i,n) {
			cin >> a[i] >> b[i];
		}
		dp.clear();
		cout << solve(n, 0, 0) << nl;
	}

	return 0;
}
