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

const float MAGIC = (float)((1<<24)-1)/1e4;
struct Float {
	unsigned char a, b, c;
	Float(float f = 0) {
		int v = round(f*MAGIC);
		a = 0xff & v>>16;
		b = 0xff & v>>8;
		c = 0xff & v;
	}
	bool operator < (const Float& v) const {
		if (a == v.a) {
			if (b == v.b) {
				return c < v.c;
			} else {
				return b < v.b;
			}
		} else {
			return a < v.a;
		}
	}
	float value() const {
		int v = ((int)a)<<16|((int)b)<<8|((int)c);
		return (float)v/MAGIC;
	}
};

const int N = 140+1;
const int M = 120+1;
const int L = N*N*M*M/4;
int grid[N][M];
Float res[L];

//#define FILEIO
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(3);
#ifdef FILEIO
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#endif

	int n, m;
	cin >> n >> m;

	int a, b;
	cin >> a >> b;

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cin >> grid[i][j];
			grid[i][j] += grid[i][j-1];
		}
	}

	for (int j = 1; j <= m; j++) {
		for (int i = 1; i <= n; i++) {
			grid[i][j] += grid[i-1][j];
		}
	}

	int sz = 0;
	for (int r = 1; r <= n; r++) {
		for (int c = 1; c <= m; c++) {
			float area = r*c;
			if (a <= area && area <= b) {
				for (int i = r; i <= n; i++) {
					for (int j = c; j <= m; j++) {
						res[sz++] = Float((grid[i][j] - grid[i-r][j] - grid[i][j-c] + grid[i-r][j-c])/area);
					}
				}
			}
		}
	}

	if (sz % 2 == 0) {
		nth_element(res, res+sz/2, res+sz);
		nth_element(res, res+sz/2-1, res+sz);
		cout << (res[sz/2].value() + res[sz/2-1].value()) / 2 << nl;
	} else {
		nth_element(res, res+sz/2, res+sz);
		cout << res[sz/2].value() << nl;
	}

	return 0;
}
