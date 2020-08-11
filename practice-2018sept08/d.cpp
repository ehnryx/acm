#include <bits/stdc++.h>
using namespace std;
#define _USE_MATH_DEFINES

typedef long long ll;
typedef long double ld;
typedef complex<ld> pt;
typedef vector<pt> pol;

const char nl = '\n';
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3f;
const ll MOD = 1e9+7;
const ld EPS = 1e-10;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

struct pii {
	int x, y;
	pii(int x=-1, int y=-1): x(x), y(y) {}
};

const int N = 25+2;
char grid[N][N];
bool reachable[N][N], vis[N][N];

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
	scanf("%d", &T);

	while (T--) {
		int n, m;
		scanf("%d %d", &n, &m);

		pii source;
		for (int i = 1; i <= n; i++) {
			scanf("%s", grid[i]+1);
			for (int j = 1; j <= m; j++) {
				if (grid[i][j] == 'S') {
					source = pii(i,j);
					grid[i][j] = '.';
				}
			}
		}

		auto init = [&] (pii s) {
			for (int i = 0; i <= m+1; i++) {
				grid[0][i] = grid[n+1][i] = '#';
			}
			for (int j = 0; j <= n+1; j++) {
				grid[j][0] = grid[j][m+1] = '#';
			}
			memset(reachable, 0, sizeof reachable);

			int res = 0;
			queue<pii> bfs;
			bfs.push(s);
			reachable[s.x][s.y] = true;
			while (!bfs.empty()) {
				pii cur = bfs.front(); bfs.pop();
				if (grid[cur.x][cur.y] == '#') continue;
				if (grid[cur.x][cur.y] == 'V') {
					res++;
					continue;
				}

				if (!reachable[cur.x-1][cur.y]) {
					bfs.push(pii(cur.x-1, cur.y));
					reachable[cur.x-1][cur.y] = true;
				}
				if (!reachable[cur.x+1][cur.y]) {
					bfs.push(pii(cur.x+1, cur.y));
					reachable[cur.x+1][cur.y] = true;
				}
				if (!reachable[cur.x][cur.y-1]) {
					bfs.push(pii(cur.x, cur.y-1));
					reachable[cur.x][cur.y-1] = true;
				}
				if (!reachable[cur.x][cur.y+1]) {
					bfs.push(pii(cur.x, cur.y+1));
					reachable[cur.x][cur.y+1] = true;
				}
			}
			return res;
		};

		auto solve = [&] (pii from, pii to) {
			pii nxt(to.x+to.x-from.x, to.y+to.y-from.y);
			if (grid[nxt.x][nxt.y] != '.') return 0;

			bool memo = reachable[nxt.x][nxt.y];
			grid[to.x][to.y] = '.';
			grid[nxt.x][nxt.y] = 'V';
			reachable[nxt.x][nxt.y] = true;
			memset(vis, 0, sizeof vis);

			int res = 0;
			queue<pii> bfs;
			bfs.push(to);
			vis[to.x][to.y] = true;
			while (!bfs.empty()) {
				pii cur = bfs.front(); bfs.pop();
				if (grid[cur.x][cur.y] == '#') continue;
				if (grid[cur.x][cur.y] == 'V') {
					if (!reachable[cur.x][cur.y]) res++;
					continue;
				}

				if (!vis[cur.x-1][cur.y]) {
					bfs.push(pii(cur.x-1, cur.y));
					vis[cur.x-1][cur.y] = true;
				}
				if (!vis[cur.x+1][cur.y]) {
					bfs.push(pii(cur.x+1, cur.y));
					vis[cur.x+1][cur.y] = true;
				}
				if (!vis[cur.x][cur.y-1]) {
					bfs.push(pii(cur.x, cur.y-1));
					vis[cur.x][cur.y-1] = true;
				}
				if (!vis[cur.x][cur.y+1]) {
					bfs.push(pii(cur.x, cur.y+1));
					vis[cur.x][cur.y+1] = true;
				}
			}

			grid[to.x][to.y] = 'V';
			grid[nxt.x][nxt.y] = '.';
			reachable[nxt.x][nxt.y] = memo;
			return res;
		};

		int pre = init(source);
		int extra = 0;
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				if (grid[i][j] == 'V' && reachable[i][j]) {
					if (grid[i-1][j] == '.' && reachable[i-1][j]) {
						extra = max(extra, solve(pii(i-1,j), pii(i,j)));
					}
					if (grid[i+1][j] == '.' && reachable[i+1][j]) {
						extra = max(extra, solve(pii(i+1,j), pii(i,j)));
					}
					if (grid[i][j-1] == '.' && reachable[i][j-1]) {
						extra = max(extra, solve(pii(i,j-1), pii(i,j)));
					}
					if (grid[i][j+1] == '.' && reachable[i][j+1]) {
						extra = max(extra, solve(pii(i,j+1), pii(i,j)));
					}
				}
			}
		}

		printf("%d\n", pre+extra);
	}

	return 0;
}
