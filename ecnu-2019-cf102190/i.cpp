#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

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

const int N = 500+1;
int in[N][N], d[N][N];

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
		int n;
		cin >> n;

		For(i,n) {
			For(j,n) {
				cin >> in[i][j];
				d[i][j] = (in[i][j] == -1 ? INF : in[i][j]);
			}
		}

		For(i,n) {
			if (d[i][i] == INF) d[i][i] = 0;
			if (d[i][i] != 0) goto bad;
			For(j,i) {
				if (d[i][j] == INF) d[i][j] = d[j][i];
				if (d[j][i] == INF) d[j][i] = d[i][j];
				if (d[i][j] != d[j][i]) goto bad;
			}
		}

		For(k,n) {
			For(i,n) {
				For(j,n) {
					if (in[i][j] == -1) d[i][j] = min(d[i][j], d[i][k]+d[k][j]);
				}
			}
		}

		For(i,n) {
			For(j,n) {
				For(k,n) {
					if (d[i][j] > d[i][k]+d[k][j]) goto bad;
				}
			}
		}

		cout << "YES" << nl;
		For(i,n) {
			For(j,n) {
				cout << (d[i][j] == INF ? INF/2 : d[i][j]) << " ";
			}
			cout << nl;
		}
		continue;

		bad:
		cout << "NO" << nl;
	}

	return 0;
}
