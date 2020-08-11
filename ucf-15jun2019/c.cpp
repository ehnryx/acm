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

const int N = 100+1;
int a[N], b[N];
int val[N][N];

int solve() {
	int n, m;
	cin >> n >> m;
	For(i,n) {
		cin >> a[i] >> b[i];
	}

	function<bool(int)> valid = [&] (int t) {
		memset(val, -1, sizeof val);
		val[0][0] = 0;
		For(i,n) {
			for (int v = 0; v <= t/a[i]; v++) {
				int u = (t-v*a[i])/b[i];
				FOR(j,0,m) {
					if (val[i][j] >= 0) {
						int jj = min(m, j+v);
						val[i+1][jj] = max(val[i+1][jj], min(m, val[i][j]+u));
					}
				}
			}
		}
		return val[n][m] == m;
	};

	int left = 0;
	int right = m * (a[0]+b[0]);
	while (left < right) {
		int mid = (left+right)/2;
		if (valid(mid)) {
			right = mid;
		} else {
			left = mid+1;
		}
	}
	cout << left << nl;

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
