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

const int N = 202;
char grid[N][N];
bool vis[N][N];

//#define FILEIO
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(10);
#ifdef FILEIO
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
#endif

	int n, m;
	cin >> n >> m;

	for (int i=1; i<=n; i++) {
		for (int j=1; j<=m; j++) {
			cin >> grid[i][j];
		}
	}

	int x, y;
	x = y = 1;
	int cnt = 0;
	for (;;) {
		if (grid[x][y] == 'T') {
			cout << cnt << nl;
			break;
		}
		if (vis[x][y]) {
			cout << "Lost" << nl;
			break;
		}
		cnt++;
		vis[x][y] = true;
		if (x==0 || x==n+1 || y==0 || y==m+1) {
			cout << "Out" << nl;
			break;
		}
		if (grid[x][y] == 'E') y++;
		else if (grid[x][y] == 'W') y--;
		else if (grid[x][y] == 'S') x++;
		else if (grid[x][y] == 'N') x--;
	}

	return 0;
}
