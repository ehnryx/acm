#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef complex<ld> pt;
typedef vector<pt> pol;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int N = 5e3+1;
int a[N], b[N], c[N], d[N];
ld dp[N][N];
int opt[N][N];

ld value(int l, int r) {
	int A = a[r]-a[l];
	int B = b[r]-b[l];
	int C = c[r]-c[l];
	int D = d[r]-d[l];
	if (A == 0) return min(B, C+D);
	if (C == 0) return min(D, A+B);
	ld x = (ld)(C+D-B)/(A+C);
	return A*x + B;
}

ld get(int i, int j, int k) {
	if (i==j) return value(j,k);
	if (j==k) return value(i,j);
	return dp[i][j] + dp[j][k];
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

	int n;
	cin >> n;

	for (int i=1; i<=n; i++) {
		cin >> a[i] >> b[i] >> c[i] >> d[i];
		a[i] += a[i-1];
		b[i] += b[i-1];
		c[i] += c[i-1];
		d[i] += d[i-1];
	}

	// Problem B.1
	cout << value(0,n) << nl;

	// Problem B.2
	ld all = 0;
	for (int i=1; i<=n; i++) {
		all += value(i-1,i);
	}
	cout << all << nl;

	int big = 0;

	// Problem B.3
	memset(opt, -1, sizeof opt);
	for (int i=0; i<=n; i++) {
		dp[i][i] = 0;
		opt[i][i] = i;
	}
	for (int l=1; l<=n; l++) {
		for (int i=0; i+l<=n; i++) {
			dp[i][i+l] = 1e42;
			//if (opt[i][i+l-1] > opt[i+1][i+l]) {
				//cerr << "OPT " << i << " " << i+l << " -> " << opt[i][i+l-1] << " vs " << opt[i+1][i+l] << nl;
			//}
			big = max(big, max(0, opt[i][i+l-1]-opt[i+1][i+l]));
			for (int j=i; j<=i+l; j++) {
			//for (int j=i; j<=i+l; j++) {
				ld cur = get(i,j,i+l);
				//cerr << "GET " << i+1 << " " << j << " : " << j+1 << " " << i+l << " -> " << cur << endl;
				if (cur < dp[i][i+l]) {
					dp[i][i+l] = cur;
					opt[i][i+l] = j;
				}
			}
			//cerr << "DP " << i+1 << " " << i+l << " : " << dp[i][i+l] << endl;
			//cerr << "OPT " << i+1 << " " << i+l << " : " << opt[i][i+l] << endl;
			assert(opt[i][i+l] != -1);
		}
	}
	cout << dp[0][n] << nl;

	// Problem B.4
	memset(opt, -1, sizeof opt);
	for (int i=0; i<=n; i++) {
		dp[i][i] = 0;
		opt[i][i] = i;
	}
	for (int l=1; l<=n; l++) {
		for (int i=0; i+l<=n; i++) {
			dp[i][i+l] = -1;
			for (int j=i; j<=i+l; j++) {
			//for (int j=i; j<=i+l; j++) {
				ld cur = get(i,j,i+l);
				//cerr << "GET " << i+1 << " " << j << " : " << j+1 << " " << i+l << " -> " << cur << endl;
				if (cur > dp[i][i+l]) {
					dp[i][i+l] = cur;
					opt[i][i+l] = j;
				}
			}
			//cerr << "DP " << i+1 << " " << i+l << " : " << dp[i][i+l] << endl;
			//cerr << "OPT " << i+1 << " " << i+l << " : " << opt[i][i+l] << endl;
			assert(opt[i][i+l] != -1);
		}
	}
	cout << dp[0][n] << nl;

	cerr << "BIG: " << big << endl;

	return 0;
}
