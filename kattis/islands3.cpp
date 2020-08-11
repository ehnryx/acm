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

vector<int> dx = { 1, -1, 0, 0 };
vector<int> dy = { 0, 0, 1, -1 };

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

	string grid[n];
	for (int i=0; i<n; i++) {
		cin >> grid[i];
	}

	int ans = 0;
	for (int i=0; i<n; i++) {
		for (int j=0; j<m; j++) {
			if (grid[i][j] == 'L') {
				ans++;
				queue<pii> bfs;
				bfs.push(pii(i,j));
				while (!bfs.empty()) {
					int x, y;
					tie(x,y) = bfs.front();
					bfs.pop();
					if (x<0||x>=n||y<0||y>=m) continue;
					if (grid[x][y]=='W') continue;
					if (grid[x][y]) {
						grid[x][y] = 0;
						for (int d=0; d<4; d++) {
							bfs.push(pii(x+dx[d],y+dy[d]));
						}
					}
				}
			}
		}
	}
	cout << ans << nl;

	return 0;
}
